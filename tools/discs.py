#!/usr/bin/env python3
"""Phase 0: unpack each disc image one at a time and keep only executables and debug candidates.

For every zip in the images directory this extracts the image into .local/tmp, lists the disc, copies
SYSTEM.CNF, the boot executable, other ELF files and symbol/map/debug candidates into
orig/<slug>/, writes the full listing and deletes the image again. Game assets are never kept.

Usage: discs.py [--images DIR] [--only SLUG ...] [--min-free-gb 12]
"""
import argparse, hashlib, json, re, shutil, subprocess, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from iso import Iso

ROOT = Path(__file__).resolve().parents[1]
SLUGS = {
    'Black (USA).zip': 'usa-retail',
    'Black (USA) (Beta) (2005-08-16).zip': 'usa-beta-2005-08-16',
    'Black (USA) (Demo).zip': 'usa-demo',
    'Black (Europe) (Beta) (2006-01-09).zip': 'eu-beta-2006-01-09',
    'Black (Europe) (En,Fr,De,Es,It).zip': 'eu-retail',
    'Black (Europe) (En,Fr,De,Es,It) (Demo).zip': 'eu-demo',
    'Black (Europe, Australia).zip': 'eu-au-retail',
    'Black (Japan).zip': 'jp-retail',
    'Black (Korea).zip': 'kr-retail',
}
KEEP_EXT = {'.map', '.sym', '.elf', '.dbg', '.stabs', '.lst', '.txt', '.xml', '.log', '.ini', '.cfg',
            '.h', '.c', '.cpp', '.mdebug', '.lnk', '.cmd', '.bat', '.py', '.pl'}
MAX_KEEP = 8 << 20


def sha256(path):
    h = hashlib.sha256()
    with open(path, 'rb') as f:
        for chunk in iter(lambda: f.read(1 << 22), b''):
            h.update(chunk)
    return h.hexdigest()


def is_texty(b):
    return bool(b) and sum(32 <= c < 127 or c in (9, 10, 13) for c in b) / len(b) > 0.95


def process(zip_path, slug, tmp, min_free):
    out = ROOT / 'orig' / slug
    out.mkdir(parents=True, exist_ok=True)
    listing = subprocess.run(['7z', 'l', '-slt', str(zip_path)], capture_output=True, text=True).stdout
    sizes = [int(m) for m in re.findall(r'^Size = (\d+)', listing, re.M)]
    need = sum(sizes)
    free = shutil.disk_usage(ROOT).free
    if free - need < min_free << 30:
        raise SystemExit(f'{slug}: free {free>>30} GB minus {need>>30} GB would drop below {min_free} GB')
    shutil.rmtree(tmp, ignore_errors=True)
    tmp.mkdir(parents=True)
    try:
        subprocess.run(['7z', 'x', '-y', '-bso0', '-bsp0', f'-o{tmp}', str(zip_path)], check=True)
        images = sorted(p for p in tmp.iterdir() if p.suffix.lower() in ('.iso', '.bin'))
        if len(images) != 1:
            raise SystemExit(f'{slug}: expected one image, got {[p.name for p in tmp.iterdir()]}')
        image = images[0]
        iso = Iso(image)
        files = sorted(iso.walk(), key=lambda t: t[1]['lba'])
        by_path = {p: r for p, r in files}
        cnf = iso.read(by_path['SYSTEM.CNF']['lba'], by_path['SYSTEM.CNF']['size'])
        boot = re.search(rb'BOOT2\s*=\s*cdrom0:\\?([^;\s]+)', cnf)
        boot_name = boot.group(1).decode() if boot else None
        listing_rows, kept = [], {}
        for p, r in files:
            head = iso.read(r['lba'], r['size'], 0, min(4096, r['size']))
            reason = None
            if p == 'SYSTEM.CNF':
                reason = 'system.cnf'
            elif p == boot_name:
                reason = 'boot'
            elif head[:4] == b'\x7fELF' and r['size'] <= 32 << 20:
                reason = 'elf'
            elif Path(p).suffix.lower() in KEEP_EXT and r['size'] <= MAX_KEEP:
                reason = 'name'
            elif '/' not in p and r['size'] <= MAX_KEEP and p != 'GLOBDATA.BIN':
                reason = 'top-level'
            elif r['size'] <= 262144 and is_texty(head) and not p.startswith('NETWORK/'):
                reason = 'text'
            listing_rows.append(dict(path=p, size=r['size'], lba=r['lba'], magic=head[:8].hex(),
                                     kept=reason))
            if reason:
                data = iso.read(r['lba'], r['size'])
                dest = out / 'files' / p
                dest.parent.mkdir(parents=True, exist_ok=True)
                dest.write_bytes(data)
                kept[p] = reason
        (out / 'listing.json').write_text(json.dumps(listing_rows, indent=1) + '\n')
        info = dict(slug=slug, zip=zip_path.name, zip_size=zip_path.stat().st_size,
                    zip_sha256=sha256(zip_path), image=image.name, image_size=image.stat().st_size,
                    image_sha256=sha256(image), sector=iso.ssize, volume=iso.volume,
                    boot=boot_name, system_cnf=cnf.decode('ascii', 'replace'), kept=kept)
        (out / 'disc.json').write_text(json.dumps(info, indent=1) + '\n')
        return info
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--images', type=Path, default=ROOT.parent / 'ps2images')
    ap.add_argument('--only', nargs='*')
    ap.add_argument('--min-free-gb', type=int, default=12)
    a = ap.parse_args()
    for zname, slug in SLUGS.items():
        if a.only and slug not in a.only:
            continue
        print('==', slug, flush=True)
        info = process(a.images / zname, slug, ROOT / '.local/tmp/disc', a.min_free_gb)
        print(info['boot'], info['image_size'], info['image_sha256'], len(info['kept']), 'kept', flush=True)


if __name__ == '__main__':
    main()
