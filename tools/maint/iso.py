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
        for size, off in self.LAYOUTS:
            self.f.seek(16 * size + off)
            pvd = self.f.read(2048)
            if pvd[:1] == b'\x01' and pvd[1:6] == b'CD001':
                self.ssize, self.off = size, off
                break
        else:
            raise ValueError('No ISO 9660 primary volume descriptor')
        self.volume = pvd[40:72].decode('ascii', 'replace').strip()
        root = self._record(pvd[156:190])
        self.root = root

    def read_sectors(self, lba, count):
        out = []
        for i in range(count):
            self.f.seek((lba + i) * self.ssize + self.off)
            out.append(self.f.read(2048))
        return b''.join(out)

    def read(self, lba, size, offset=0, length=None):
        length = size - offset if length is None else min(length, size - offset)
        first, skip = divmod(offset, 2048)
        data = self.read_sectors(lba + first, (skip + length + 2047) // 2048)
        return data[skip:skip + length]

    @staticmethod
    def _record(b):
        lba, = struct.unpack_from('<I', b, 2)
        size, = struct.unpack_from('<I', b, 10)
        flags = b[25]
        n = b[32]
        name = b[33:33 + n]
        return dict(lba=lba, size=size, dir=bool(flags & 2), raw=name)

    def walk(self, node=None, path=''):
        """Yield (path, record) for every file; directories are recursed."""
        node = node or self.root
        data = self.read(node['lba'], node['size'])
        pos = 0
        while pos < len(data):
            n = data[pos]
            if n == 0:
                pos = (pos // 2048 + 1) * 2048
                continue
            rec = self._record(data[pos:pos + n])
            pos += n
            if rec['raw'] in (b'\x00', b'\x01'):
                continue
            name = rec['raw'].decode('ascii', 'replace')
            if not rec['dir']:
                name = name.rsplit(';', 1)[0] if ';' in name else name
            rec['path'] = path + '/' + name if path or True else name
            rec['path'] = (path + '/' + name).lstrip('/')
            if rec['dir']:
                yield from self.walk(rec, rec['path'])
            else:
                yield rec['path'], rec
