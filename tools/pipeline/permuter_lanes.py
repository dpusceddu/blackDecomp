#!/usr/bin/env python3
"""Worker-only supervisor for disjoint durable permuter search lanes.

Launch through permuter_service.py --lanes; this module never runs SDK tools on
its own. One parent owns the queue and status, while lane children exclusively
own individual function checkpoints and separate compiler working directories.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import time


def pending_keys(records, states, active):
    """Assign the globally largest available function, excluding leased keys."""
    return sorted((key for key, state in states.items()
                   if key not in active and state['state'] in ('queued', 'running')),
                  key=lambda key: (-records[key]['function']['size'],
                                   records[key]['saved_differing_instructions'], key))


def preemption_key(records, states, active):
    """Only a newly larger pending function displaces the smallest active one."""
    pending = pending_keys(records, states, active)
    if not pending or not active:
        return None
    smallest = min(active, key=lambda key: (records[key]['function']['size'], key))
    if records[pending[0]]['function']['size'] > records[smallest]['function']['size']:
        return smallest
    return None


def budget_finished(manifest, elapsed, now):
    """A restart preserves accumulated wall time and the absolute end time."""
    return elapsed >= manifest['total_hours'] * 3600 or (
        manifest.get('deadline_unix') is not None and now >= manifest['deadline_unix'])


def reconcile_state(record, state, integrated, hours_per_function, directory=None):
    """Preserve RNG/best/elapsed for unchanged inputs when a lane restarts."""
    from permuter_worker import reconcile_integrated, refresh_record_state
    if state.get('input_hash') != record['input_hash']:
        state = refresh_record_state(record, state, directory)
    else:
        state = dict(state)
        if state.get('state') == 'running':
            state['state'] = 'queued'
    if record.get('unsupported'):
        state.update(state='unsupported', reason=record['unsupported'])
    elif state.get('state') == 'budget-exhausted' and state['elapsed_seconds'] < hours_per_function * 3600:
        state['state'] = 'queued'
    reconcile_integrated(state, record['key'], integrated)
    return state


def supervise(work, manifest):
    """Run isolated compiler children; only this process dispatches or preempts."""
    from permuter_worker import atomic_json, ingest_submissions, retained_wins
    work = work.resolve()
    output = work / 'output'
    output.mkdir(exist_ok=True)
    status_path = output / 'status.json'
    old = json.loads(status_path.read_text()) if status_path.exists() else {}
    past_seconds = old.get('elapsed_seconds', 0)
    started = time.monotonic()
    records = {record['key']: record for record in manifest['queue']}
    integrated = set(manifest.get('integrated_addresses', []))
    states, children = {}, {}
    lane_seconds = {str(i): old.get('lane_wall_seconds', {}).get(str(i), 0)
                    for i in range(manifest['lanes'])}
    accounting_started = old.get('lane_accounting_started_unix', time.time())
    stop = [False]
    for sig in (signal.SIGTERM, signal.SIGINT):
        signal.signal(sig, lambda *_: stop.__setitem__(0, True))

    def elapsed():
        return past_seconds + time.monotonic() - started

    def read_state(key):
        path = output / key / 'state.json'
        return json.loads(path.read_text()) if path.exists() else {}

    def save_state(key, state):
        path = output / key / 'state.json'
        path.parent.mkdir(exist_ok=True)
        atomic_json(path, state)

    def active_keys():
        return {child['key'] for child in children.values()}

    def stop_child(lane):
        child = children[lane]
        child['process'].terminate()
        try:
            child['process'].wait(timeout=25)
        except subprocess.TimeoutExpired:
            child['process'].kill()
            child['process'].wait()
        reap(lane)

    def reap(lane):
        child = children.pop(lane)
        lane_seconds[str(lane)] += time.monotonic() - child['started']
        child['log'].close()
        key = child['key']
        state = reconcile_state(records[key], read_state(key), integrated, manifest['hours_per_function'], output / key)
        # A crashing compiler child must not spin forever on the same baseline.
        if child['process'].returncode and state.get('state') == 'queued' and not child.get('interrupted'):
            state.update(state='worker-failed', reason='lane child exited with code %s' % child['process'].returncode)
        states[key] = state
        save_state(key, state)

    def refresh():
        ingest_submissions(records, work / 'inbox')
        for lane, child in list(children.items()):
            key = child['key']
            if records[key]['input_hash'] != child['input_hash'] or key in integrated:
                child['interrupted'] = True
                stop_child(lane)
        active = active_keys()
        for key, record in records.items():
            state = read_state(key)
            if key not in active:
                state = reconcile_state(record, state, integrated, manifest['hours_per_function'], output / key)
                if state != states.get(key):
                    save_state(key, state)
            states[key] = state

    def launch(lane, key):
        lane_work = work / 'lanes' / str(lane)
        lane_work.mkdir(parents=True, exist_ok=True)
        for name in ('tools', 'vendor'):
            link = lane_work / name
            if not link.exists():
                link.symlink_to(work / name, target_is_directory=True)
        shutil.copytree(work / 'include', lane_work / 'include', dirs_exist_ok=True)
        child_manifest = dict(manifest, lanes=1, queue=[records[key]])
        atomic_json(lane_work / 'queue.json', child_manifest)
        (lane_work / 'inbox').mkdir(exist_ok=True)
        lane_output = output / 'lanes' / str(lane)
        lane_output.mkdir(parents=True, exist_ok=True)
        log = (lane_output / 'worker.log').open('a')
        process = subprocess.Popen([sys.executable, str(work / 'tools/permuter_worker.py'),
                                    '--work', str(lane_work), '--output', str(output),
                                    '--status-file', str(lane_output / 'status.json'), '--no-wins-index'],
                                   cwd=lane_work, stdout=log, stderr=subprocess.STDOUT)
        children[lane] = dict(key=key, input_hash=records[key]['input_hash'], process=process,
                              started=time.monotonic(), log=log)

    def status(state='running'):
        counts = {}
        for key, value in states.items():
            kind = 'running' if key in active_keys() else value.get('state', 'queued')
            counts[kind] = counts.get(kind, 0) + 1
        wins = retained_wins(output)
        atomic_json(output / 'wins.json', wins)
        wall = dict(lane_seconds)
        for lane, child in children.items():
            wall[str(lane)] += time.monotonic() - child['started']
        active = {str(lane): child['key'] for lane, child in sorted(children.items())}
        atomic_json(status_path, dict(
            state=state, active=next(iter(active.values()), None), active_lanes=active,
            lanes=manifest['lanes'], queue=len(records), counts=counts,
            elapsed_seconds=elapsed(), container_wall_seconds=elapsed(), lane_wall_seconds=wall,
            lane_accounting_started_unix=accounting_started,
            retained_function_search_seconds=sum(s.get('elapsed_seconds', 0) for s in states.values()),
            total_budget_seconds=manifest['total_hours'] * 3600,
            deadline_unix=manifest.get('deadline_unix'),
            candidates=sum(s.get('tried', 0) for s in states.values()),
            exact_candidates=sorted(set(wins) | {k for k, s in states.items() if s.get('state') == 'exact'}),
            permuter_wins=sorted(wins),
            improved=[k for k, s in states.items() if s.get('best_rank', [10**9]) < s.get('baseline_rank', [10**9])],
            updated_unix=time.time(), permuter_commit=manifest['permuter_commit']))

    checkpoint = 0
    final_state = 'budget-exhausted'
    try:
        while not stop[0] and not budget_finished(manifest, elapsed(), time.time()):
            for lane, child in list(children.items()):
                if child['process'].poll() is not None:
                    reap(lane)
            if time.monotonic() - checkpoint >= 5:
                refresh()
                victim = preemption_key(records, states, active_keys())
                if victim and len(children) == manifest['lanes']:
                    lane = next(lane for lane, child in children.items() if child['key'] == victim)
                    children[lane]['interrupted'] = True
                    stop_child(lane)
                pending = pending_keys(records, states, active_keys())
                for lane in range(manifest['lanes']):
                    if lane not in children and pending:
                        launch(lane, pending.pop(0))
                status()
                checkpoint = time.monotonic()
                if not children and not pending:
                    final_state = 'complete'
                    return
            time.sleep(.25)
    finally:
        for lane, child in list(children.items()):
            child['interrupted'] = True
            stop_child(lane)
        refresh()
        status('stopped' if stop[0] else final_state)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()
    parser.error('Worker-only helper; use permuter_service.py start --lanes instead.')
