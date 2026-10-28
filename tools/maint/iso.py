"""Minimal ISO 9660 reader for plain ISO (2048) and raw CD images (MODE1/MODE2, 2352)."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import struct


class Iso:
    LAYOUTS = ((2048, 0), (2352, 16), (2352, 24), (2336, 8))  # (sector size, user-data offset)

    def __init__(self, path):
        self.f = open(path, 'rb')
        try:
            self.f.seek(0, 2)
            self.image_size = self.f.tell()
            for size, off in self.LAYOUTS:
                self.f.seek(16 * size + off)
                pvd = self.f.read(2048)
                if len(pvd) == 2048 and pvd[:1] == b'\x01' and pvd[1:6] == b'CD001':
                    self.ssize, self.off = size, off
                    break
            else:
                raise ValueError('No ISO 9660 primary volume descriptor')
            self.volume = pvd[40:72].decode('ascii', 'replace').strip()
            self.root = self._record(pvd[156:190])
        except Exception:
            self.f.close()
            raise

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.f.close()

    def read_sectors(self, lba, count):
        out = []
        for i in range(count):
            self.f.seek((lba + i) * self.ssize + self.off)
            out.append(self.f.read(2048))
        return b''.join(out)

    def read(self, lba, size, offset=0, length=None):
        length = size - offset if length is None else min(length, size - offset)
        if min(lba, size, offset, length) < 0:
            raise ValueError('Invalid ISO file extent')
        first, skip = divmod(offset, 2048)
        count = (skip + length + 2047) // 2048
        if count and (lba + first + count - 1) * self.ssize + self.off + 2048 > self.image_size:
            raise ValueError('Truncated ISO file extent')
        data = self.read_sectors(lba + first, count)
        return data[skip:skip + length]

    @staticmethod
    def _record(b):
        if len(b) < 34 or b[32] == 0 or 33 + b[32] > len(b):
            raise ValueError('Invalid ISO directory record')
        lba, = struct.unpack_from('<I', b, 2)
        size, = struct.unpack_from('<I', b, 10)
        flags = b[25]
        n = b[32]
        name = b[33:33 + n]
        return dict(lba=lba, size=size, dir=bool(flags & 2), raw=name)

    def entries(self, node):
        """Yield the direct children of a directory without visiting unrelated directories."""
        if not node['dir'] or node['size'] > 16 << 20:
            raise ValueError('Invalid or oversized ISO directory')
        data = self.read(node['lba'], node['size'])
        pos = 0
        while pos < len(data):
            n = data[pos]
            if n == 0:
                pos = (pos // 2048 + 1) * 2048
                continue
            if pos % 2048 + n > 2048 or pos + n > len(data):
                raise ValueError('Invalid ISO directory record length')
            rec = self._record(data[pos:pos + n])
            pos += n
            if rec['raw'] in (b'\x00', b'\x01'):
                continue
            name = rec['raw'].decode('ascii', 'replace')
            if not rec['dir']:
                name = name.rsplit(';', 1)[0] if ';' in name else name
            yield name, rec

    def find(self, path):
        """Find one disc path, ignoring ISO version suffixes and filename case."""
        node = self.root
        parts = path.replace('\\', '/').strip('/').split('/')
        if any(part in ('', '.', '..') for part in parts):
            raise ValueError('Invalid ISO path')
        for part in parts:
            node = next((rec for name, rec in self.entries(node) if name.upper() == part.upper()), None)
            if node is None:
                raise ValueError('ISO is missing %s' % path)
        return node

    def walk(self, node=None, path='', _seen=None):
        """Yield (path, record) for every file; directories are recursed."""
        node = node or self.root
        seen = set() if _seen is None else _seen
        if node['lba'] in seen:
            raise ValueError('Cyclic ISO directory')
        seen.add(node['lba'])
        for name, rec in self.entries(node):
            rec['path'] = (path + '/' + name).lstrip('/')
            if rec['dir']:
                yield from self.walk(rec, rec['path'], seen)
            else:
                yield rec['path'], rec
