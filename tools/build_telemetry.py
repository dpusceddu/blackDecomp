"""Append small worker-call records under ignored build directories."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json
import os
import time
import uuid
from pathlib import Path


def record(build, kind, status, call_id=None, **fields):
    call_id = call_id or uuid.uuid4().hex
    directory = Path(build) / 'telemetry'
    directory.mkdir(parents=True, exist_ok=True)
    row = dict(time=time.time(), pid=os.getpid(), kind=kind, status=status,
               call_id=call_id, **fields)
    # Each process owns its ledger; later calls append instead of overwriting
    # the job plan. A killed process leaves a submitted call without completion.
    with (directory / ('calls-%d.jsonl' % os.getpid())).open('a') as stream:
        stream.write(json.dumps(row, sort_keys=True) + '\n')
    return call_id
