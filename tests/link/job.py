# Runs inside the build job: assemble a GNU object with the EE assembler, link it with an SN-compiled object using the
# mainline MIPS ld and a trivial linker script, then inspect the result.
import subprocess
def sh(c):
    p = subprocess.run(c, shell=True, capture_output=True, text=True)
    print('$', c)
    print(p.stdout + p.stderr)
    return p.returncode
sh('/toolchains/compilers/ee-gcc2.96/ee/bin/as -o extern.o extern.s')
rc = sh('mipsel-linux-gnu-ld -m elf32ltsmip -T probe.ld -o probe.elf extern.o c.o')
sh('mipsel-linux-gnu-readelf -hS probe.elf | grep -E "Machine|Entry|Flags|\\.text|\\.data|\\.scommon"')
sh('mipsel-linux-gnu-nm probe.elf')
sh('mipsel-linux-gnu-objdump -d probe.elf | sed -n "/<bump>/,$ p" | head -8')
raise SystemExit(rc)
