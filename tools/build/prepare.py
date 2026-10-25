#!/usr/bin/env python3
"""Run one source-generation stage; each invocation records its complete output inventory."""
import argparse
import json
import os
from pathlib import Path
import runpy
import sys
import yaml


def tool(name, *args):
    sys.argv = [name]+list(args)
    try:
        runpy.run_path(name, run_name='__main__')
    except SystemExit as error:
        if error.code not in (None, 0):
            raise


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('stage',choices=['extract','split'])
    p.add_argument('version')
    a=p.parse_args()
    if a.stage=='extract':
        tool('tools/build/splat_config.py',a.version)
        tool('tools/build/elf_layout.py',a.version)
    else:
        # Remove only files this splat invocation previously produced. Other
        # generators own nonmatchings/ and the assembly-only text aggregate.
        inventory=Path(os.environ.get('BLACK_NINJA_RECORD','build/'+a.version+'/prepare/split.json'))
        if inventory.is_file():
            for name in json.loads(inventory.read_text())['writes']:
                if name.startswith(('asm/'+a.version+'/', 'data/'+a.version+'/')):
                    Path(name).unlink(missing_ok=True)
        # Upstream textbin/databin preserves an existing assembly wrapper.
        # Recover it even if this stage's own output inventory was deleted.
        config=yaml.safe_load((Path('build')/a.version/'splat.yaml').read_text())
        for segment in config['segments']:
            if not isinstance(segment,dict):
                continue
            for sub in segment.get('subsegments',[]):
                if isinstance(sub,list) and len(sub)>2 and sub[1] in ('textbin','databin','rodatabin'):
                    (Path(config['options']['asm_path'])/config['options']['data_path']/(sub[2]+'.s')).unlink(missing_ok=True)
        # splat writes this only when its content changes; remove its old
        # comparison copy so discovery records the linker script as an output.
        (Path('build')/a.version/(a.version+'.ld')).unlink(missing_ok=True)
        sys.argv=['splat','split','build/'+a.version+'/splat.yaml']
        runpy.run_module('splat',run_name='__main__')


if __name__=='__main__':
    main()
