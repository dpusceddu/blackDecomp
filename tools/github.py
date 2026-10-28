#!/usr/bin/env python3
"""Check Git identity and GitHub access for contribution sessions against the main repository.

Usage: python3 tools/github.py
Read-only checks; never logs in, creates a fork, pushes or opens a pull request.
Authentication and repository access do not prove push permission: the session must push its claim before editing.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPOSITORY = 'dpusceddu/blackDecomp'


def contribution_problem(root=ROOT):
    """Return an actionable problem, or None; suppress command output containing account details."""
    if not shutil.which('gh'):
        return 'install GitHub CLI (gh), then run gh auth login --hostname github.com'
    checks = [
        (['git', 'var', 'GIT_AUTHOR_IDENT'], 'configure your Git author name and email before starting a session'),
        (['git', 'var', 'GIT_COMMITTER_IDENT'], 'configure your Git committer name and email before starting a session'),
        (['gh', 'api', '--hostname', 'github.com', 'user', '--jq', '.login'],
         'GitHub authentication failed; run gh auth login --hostname github.com'),
        (['gh', 'repo', 'view', REPOSITORY, '--json', 'nameWithOwner'],
         'cannot read %s; check GitHub access and network connectivity' % REPOSITORY),
    ]
    for command, problem in checks:
        try:
            result = subprocess.run(command, cwd=root, capture_output=True, text=True, timeout=30)
        except (OSError, subprocess.TimeoutExpired):
            return problem
        if result.returncode:
            return problem
    return None


if __name__ == '__main__':
    problem = contribution_problem()
    if problem:
        raise SystemExit(problem)
    print('Git identity and GitHub access ready for %s.' % REPOSITORY)
