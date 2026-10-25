#!/usr/bin/env python3
"""Generate the USA function inventory used by the TU map and source analysis tools."""
import argparse
import os
from pathlib import Path
import sys
sys.path[:0]=[str(Path(__file__).resolve().parents[1]/d) for d in ('','build','pipeline','maint')]


def main():
    argparse.ArgumentParser(description=__doc__).parse_args()
    os.environ['BLACK_INVENTORY_WRITE']='1'
    import autodecomp
    autodecomp.load_inventory()


if __name__=='__main__':
    main()
