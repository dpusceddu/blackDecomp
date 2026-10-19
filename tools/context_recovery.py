#!/usr/bin/env python3
"""Recover PS2 call and layout constraints; never execute target tools on the host.

The ignored build/auto/context.json keeps conflicting evidence and unproved leads.
Generated headers are PS2 access views, not claims about allocation size or C++ inheritance.
Only a source function which actually accesses a generated view can verify that view.
"""
import argparse
import collections
import hashlib
import json
import re
import struct
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VERSION = 10
POINTER_ALIASES = set()
CLASS_NAMES = set()
NAMESPACE_NAMES = set()
STATIC_METHODS = set()
# 64-bit integers are long on the target; long long is 128-bit (SN EE).
SCALARS = {'void': 'void', 'bool': 'u8', 'char': 's8', 'signed char': 's8', 'unsigned char': 'u8',
           'short': 's16', 'short int': 's16', 'unsigned short': 'u16', 'int': 's32', 'unsigned': 'u32',
           'unsigned int': 'u32', 'long': 's64', 'long int': 's64', 'unsigned long': 'u64',
           'long long': 's128', 'unsigned long long': 'u128', 'float': 'f32', 'double': 'f64',
           'uchar': 'u8', 'ushort': 'u16', 'uint': 'u32', 'ulong': 'u64', 'byte': 'u8', 'word': 'u16',
           'dword': 'u32', 'undefined1': 'u8', 'undefined2': 'u16', 'undefined4': 'u32',
           'undefined8': 'u64', 'qword': 'u64', 'longlong': 's64', 'ulonglong': 'u64'}
SCALARS.update({'M2C_UNK': 's32', 'M2C_UNK8': 's8', 'M2C_UNK16': 's16', 'M2C_UNK32': 's32', 'M2C_UNK64': 's64'})
SCALARS.update({'signed short': 's16', 'signed short int': 's16', 'signed': 's32',
                'signed int': 's32', 'signed long': 's64', 'signed long int': 's64',
                'signed long long': 's128'})
for _t in ('s8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 's128', 'u128', 'f32', 'f64'):
    SCALARS[_t] = _t
WIDTH = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 's64': 8, 'u64': 8,
         's128': 16, 'u128': 16, 'f32': 4, 'f64': 8, 'void *': 4}
MEMORY = {'lb': ('s8', 1), 'lbu': ('u8', 1), 'sb': ('u8', 1), 'lh': ('s16', 2), 'lhu': ('u16', 2),
          'sh': ('u16', 2), 'lw': ('s32', 4), 'lwu': ('u32', 4), 'sw': ('u32', 4),
          'ld': ('s64', 8), 'sd': ('u64', 8), 'lq': ('s128', 16), 'sq': ('u128', 16),
          'lwc1': ('f32', 4), 'swc1': ('f32', 4), 'lqc2': ('u128', 16), 'sqc2': ('u128', 16)}
COMMENT = re.compile(r'/\*.*?\*/|//[^\n]*', re.S)


def split_params(text):
    """Split declarators without splitting function-pointer arguments or templates."""
    out, start, depth = [], 0, 0
    for i, c in enumerate(text):
        depth += c in '([<'
        depth -= c in ')]>'
        if c == ',' and depth == 0:
            out.append(text[start:i].strip())
            start = i + 1
    out.append(text[start:].strip())
    return [] if out == [''] or out == ['void'] else out


def type_spelling(text):
    text = re.sub(r'\b(const|volatile|register|extern|static|inline|virtual|__inline__|__stdcall|__cdecl|__thiscall|__fastcall)\b', '', text)
    return ' '.join(text.split()).strip()


def strip_attributes(text):
    """Remove balanced GNU attributes without dropping their ABI-relevant mode."""
    attrs = []
    while match := re.search(r'\b__attribute__\s*\(', text):
        end, depth = match.end(), 1
        while end < len(text) and depth:
            depth += text[end] == '('
            depth -= text[end] == ')'
            end += 1
        if depth:
            break
        attrs.append(text[match.start():end])
        text = text[:match.start()] + text[end:]
    return text, ' '.join(attrs)


def lexical_type_scopes(text):
    """Named type scopes and direct declaration depth; function-local aliases stay local."""
    mask = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda m: ''.join('\n' if c == '\n' else ' ' for c in m.group()), text)
    stack, ends, depths = [], {}, []
    for pos, char in enumerate(mask):
        depths.append(len(stack))
        if char == '{':
            stack.append(pos)
        elif char == '}' and stack:
            ends[stack.pop()] = pos
    scopes = []
    pattern = r'\b(namespace|class|struct)\s+(\w+(?:::\w+)*)?\s*(?:final\s*)?(?::[^;{]+)?\{'
    for match in re.finditer(pattern, mask):
        if re.search(r'\benum\s*$', mask[max(0, match.start()-30):match.start()]):
            continue
        opening = match.end()-1
        if opening in ends:
            scopes.append((opening, ends[opening], tuple((match.group(2) or '').split('::')) if match.group(2) else ()))
    # Linkage braces are transparent to lookup, unlike function/initializer braces.
    for match in re.finditer(r'\bextern\s+"C"\s*\{', text):
        opening = match.end()-1
        if opening in ends:
            scopes.append((opening, ends[opening], ()))
    scopes.sort()
    return scopes, depths


def scope_at(scopes, pos):
    return tuple(name for begin, end, names in scopes if begin < pos < end for name in names)


class ScopedAliases:
    """Conservative scalar typedef lookup within one TU's quoted-header context.

    Names such as Value are never assigned a global width. Only a visible typedef/using
    chain to a known target scalar proves it; conflicts and unsupported aliases stay unknown.
    This is not a preprocessor or a complete C++ parser.
    """
    def __init__(self, texts=()):
        self.aliases = collections.defaultdict(set)
        for text in texts:
            self.add_text(text)

    def add_text(self, text):
        text = COMMENT.sub('', text)
        scopes, depths = lexical_type_scopes(text)
        declarations = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                              lambda m: ' ' * len(m.group()), text)
        pattern = r'\b(typedef)\s+([^;{}]+);|\b(using)\s+([^;{}]+);'
        for match in re.finditer(pattern, declarations):
            containing = [s for s in scopes if s[0] < match.start() < s[1]]
            if depths[match.start()] != len(containing):
                continue
            scope = scope_at(scopes, match.start())
            raw = match.group(2) or match.group(4)
            plain, attrs = strip_attributes(raw)
            mode = re.search(r'\bmode\s*\(\s*(__)?([A-Z]+)(__)?\s*\)', attrs)
            mode = mode.group(2) if mode else None
            if match.group(1):
                declaration = re.fullmatch(r'\s*(.*?)\s+([A-Za-z_]\w*)\s*', plain, re.S)
                if not declaration:
                    continue
                target, name = declaration.groups()
            else:
                declaration = re.fullmatch(r'\s*([A-Za-z_]\w*)\s*=\s*(.*?)\s*', plain, re.S)
                if declaration:
                    name, target = declaration.groups()
                elif re.fullmatch(r'\s*(?:::)?\w+(?:::\w+)+\s*', plain):
                    target = plain.strip()
                    name = target.rsplit('::', 1)[-1]
                else:
                    continue  # using namespace/template/function imports need richer lookup.
            self.aliases[scope + (name,)].add((type_spelling(target), scope, mode))

    def scalar(self, text, scope=(), seen=frozenset()):
        text = type_spelling(text)
        absolute = text.startswith('::')
        parts = tuple(text.lstrip(':').split('::'))
        prefixes = [()] if absolute else [scope[:n] for n in range(len(scope), -1, -1)]
        for prefix in prefixes:
            key = prefix + parts
            if key not in self.aliases:
                continue
            if key in seen:
                return 'unknown'
            resolved = set()
            for target, origin, mode in self.aliases[key]:
                value = self.scalar(target, origin, seen | {key})
                if mode:
                    bits = {'QI': 8, 'HI': 16, 'SI': 32, 'DI': 64, 'TI': 128}.get(mode)
                    value = value[0] + str(bits) if bits and re.fullmatch(r'[su]\d+', value) else 'unknown'
                resolved.add(value)
            return next(iter(resolved)) if len(resolved) == 1 else 'unknown'
        return SCALARS.get(text, 'unknown')


def normalize_type(text, ghidra=False, aliases=None, scope=()):
    text = type_spelling(text)
    scalar_type = lambda name: aliases.scalar(name, scope) if aliases else SCALARS.get(name, 'unknown')
    if text in POINTER_ALIASES and scalar_type(text) == 'unknown':
        return 'void *', None
    if '(*' in text or '[' in text or '&' in text or '*' in text:
        base = re.sub(r'\b(struct|class)\s+', '', text).split('*')[0].split('&')[0].strip()
        scalar = scalar_type(base)
        cls = base if re.fullmatch(r'[A-Za-z_]\w*(?:::\w+)*', base) and scalar == 'unknown' else None
        return (scalar + ' ' + '*' * max(1, text.count('*')) if scalar not in ('unknown', 'void') else 'void *'), cls
    # Ghidra's data model is not SN's spelling: undefined8/longlong are eight bytes.
    return scalar_type(text), None


def param_type(text, aliases=None, scope=()):
    text = text.split('=')[0].strip()
    if text == '...':
        return '...', None
    if re.search(r'\(\s*\*', text):
        return 'void *', None
    # A lone known type or Foo* is an unnamed parameter, not a name to strip.
    if text in SCALARS or text in POINTER_ALIASES or text.endswith(('*', '&')) or (aliases and aliases.scalar(text, scope) != 'unknown'):
        return normalize_type(text, aliases=aliases, scope=scope)
    text = re.sub(r'\b[A-Za-z_]\w*\s*(\[[^]]*\])?$', lambda m: '*' if m.group(1) else '', text)
    return normalize_type(text, aliases=aliases, scope=scope)


def lexical_class_scopes(text):
    """Direct member depth, excluding braces inside literals and nested function bodies."""
    mask = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda m: ''.join('\n' if c == '\n' else ' ' for c in m.group()), text)
    stack, ends, depths = [], {}, []
    for i, c in enumerate(mask):
        depths.append(len(stack))
        if c == '{':
            stack.append(i)
        elif c == '}' and stack:
            ends[stack.pop()] = i
    scopes = []
    for m in re.finditer(r'\b(?:class|struct)\s+(\w+)\s*(?:final\s*)?(?::[^;{]+)?\{', mask):
        if re.search(r'\benum\s*$', mask[max(0, m.start()-30):m.start()]):
            continue
        opening = m.end()-1
        if opening in ends:
            scopes.append((opening, ends[opening], m.group(1), depths[opening]+1))
            CLASS_NAMES.add(m.group(1))
    return scopes, depths


def parse_declarations(text, aliases=None):
    """Find C/C++ signatures and function bodies without requiring a modern C++ parser.

    Unsupported declarators are retained as unknown instead of guessed as int. GNU asm aliases
    and the *_FUNCTION(address) aliases used by PS2 headers are recognized before preprocessing.
    """
    text = COMMENT.sub('', text)
    aliases = aliases or ScopedAliases([text])
    type_scopes, _ = lexical_type_scopes(text)
    scopes, depths = lexical_class_scopes(text)
    pattern = re.compile(r'(?:^|[;{}\n])\s*([^;{}#\n]*?)(?<!\w)(~?[A-Za-z_]\w*(?:::[~A-Za-z_]\w*)*)\s*\(', re.M)
    result = []
    for m in pattern.finditer(text):
        name, left = m.group(2), m.group(1).strip()
        if re.search(r'\b(return|throw|new|delete|case|if|for|while)\b|[=+!]|->', left):
            continue
        if name in ('if', 'for', 'while', 'switch', 'return', '__attribute__', '__asm__', 'sizeof'):
            continue
        if '::' not in name:
            containing = [s for s in scopes if s[0] < m.start(2) < s[1]]
            if containing and depths[m.start(2)] == containing[-1][3]:
                name = '::'.join(s[2] for s in containing) + '::' + name
        depth, j = 1, m.end()
        while j < len(text) and depth:
            depth += text[j] == '('
            depth -= text[j] == ')'
            j += 1
        if depth:
            continue
        params = text[m.end():j - 1]
        tail = text[j:]
        stop = re.search(r'[;{]', tail)
        if not stop or stop.start() > 250:
            continue
        attrs = tail[:stop.start()]
        if attrs.strip() and not re.fullmatch(r'(?:\s*(?:const|noexcept|override|final)|\s*(?:__asm__|__attribute__|\w+_FUNCTION)\s*\(.*\))*\s*', attrs, re.S):
            continue
        method = name.rsplit('::', 1)
        qualification = method[0] if len(method) == 2 else None
        cls = qualification
        if cls and cls.split('::')[-1] in NAMESPACE_NAMES and cls.split('::')[-1] not in CLASS_NAMES:
            cls = None
        short = method[-1]
        ctor = cls and short.lstrip('~') == cls.split('::')[-1]
        if not left and not ctor:
            continue
        type_scope = scope_at(type_scopes, m.start(2))
        if qualification:
            parts = tuple(qualification.split('::'))
            if type_scope[-len(parts):] != parts:
                type_scope = parts if parts[:len(type_scope)] == type_scope else type_scope + parts
        ret, retclass = ('void *', cls) if ctor and not short.startswith('~') else (('void', None) if ctor else normalize_type(left, aliases=aliases, scope=type_scope))
        ps = [param_type(p, aliases=aliases, scope=type_scope) for p in split_params(params)]
        implicit_this = bool(cls and 'static' not in left.split() and (cls.split('::')[-1], short) not in STATIC_METHODS)
        if implicit_this:
            ps = [('void *', cls)] + ps
        uncertainty = []
        if cls and cls.split('::')[-1] not in CLASS_NAMES:
            uncertainty.append('qualified scope is not proved to be a class')
        if ctor:
            uncertainty.append('constructor/destructor may have hidden in-charge argument')
        if ret == 'unknown':
            uncertainty.append('unresolved return type may need hidden aggregate-return pointer')
        alias = re.search(r'__asm__\s*\(\s*"(func_[0-9A-Fa-f]{8})"', attrs)
        macro = re.search(r'\b\w+_FUNCTION\s*\(\s*([0-9A-Fa-f]{8})\s*\)', attrs)
        address = int(alias.group(1)[5:], 16) if alias else (int(macro.group(1), 16) if macro else None)
        body = ''
        if stop.group() == '{':
            begin, k, d = j + stop.start() + 1, j + stop.start() + 1, 1
            while k < len(text) and d:
                d += text[k] == '{'
                d -= text[k] == '}'
                k += 1
            body = text[begin:k - 1]
        qualified_name = '::'.join((*type_scope, short))
        result.append(dict(name=name, qualified_name=qualified_name, short=short, cls=cls, ret=ret, retclass=retclass, params=ps,
                           address=address, body=body, abi_uncertainty=uncertainty, implicit_this=implicit_this, raw=left + ' ' + name + '(' + params + ')'))
    return result


def demangle_method(symbol):
    """Read old-GCC owner scopes, not argument encodings or template spellings."""
    if symbol.startswith(('_$_', '_._')):
        method, owner = '_', symbol[3:]
    else:
        match = re.match(r'^(.*?)__([CV]*(?:Q[1-9]|[1-9]).*)$', symbol)
        if not match:
            return None
        method, owner = match.groups()
    owner = owner.lstrip('CV')  # const/volatile member qualifiers precede the owner.
    count = 1
    if owner.startswith('Q'):
        match = re.match(r'Q([1-9])', owner)
        if not match:
            return None
        count, owner = int(match[1]), owner[match.end():]
    scopes = []
    for _ in range(count):
        match = re.match(r'([1-9][0-9]*)', owner)
        if not match:
            return None
        length = int(match[1])
        part = owner[match.end():match.end() + length]
        if len(part) != length or not re.fullmatch(r'[A-Za-z_]\w*', part):
            return None
        scopes.append(part)
        owner = owner[match.end() + length:]
    cls = scopes[-1]
    if not method:
        method = cls
    elif method == '_':
        method = '~' + cls
    return '::'.join(scopes + [method])


def source_seeds(root=ROOT, matched_only=False):
    from units import load_units, dependencies
    seeds, evidence, parsed, texts = {}, [], {}, {}
    units = load_units(root / 'config/units.yaml', variant='usa-retail')
    for p in (root / 'include').rglob('*'):
        if p.suffix in ('.h', '.hpp') and 'recovered' not in p.parts:
            text = COMMENT.sub('', p.read_text())
            CLASS_NAMES.update(re.findall(r'\b(?:class|struct)\s+(\w+)', text))
            NAMESPACE_NAMES.update(re.findall(r'\bnamespace\s+(\w+)', text))
            for cm in re.finditer(r'\b(?:class|struct)\s+(\w+)[^;{]*\{', text):
                begin, depth, end = cm.end(), 1, cm.end()
                while end < len(text) and depth:
                    depth += text[end] == '{'
                    depth -= text[end] == '}'
                    end += 1
                STATIC_METHODS.update((cm.group(1), method) for method in re.findall(r'\bstatic\s+[^;{}]*?\b(\w+)\s*\(', text[begin:end-1]))
            POINTER_ALIASES.update(re.findall(r'typedef\s+[^;]+?\(\s*\*\s*(\w+)\s*\)', text, re.S))
            POINTER_ALIASES.update(re.findall(r'typedef\s+[^;()]+?\*\s*(\w+)\s*;', text))
    for u in units:
        paths = [str(p) for p in dependencies(u['source'])]
        for path in paths:
            if path not in texts:
                texts[path] = (root / path).read_text()
        scoped_aliases = ScopedAliases(texts[p] for p in paths)
        context = frozenset((name, frozenset(values)) for name, values in scoped_aliases.aliases.items())
        decls = []
        for path in paths:
            key = path, context
            if key not in parsed:
                parsed[key] = parse_declarations(texts[path], aliases=scoped_aliases)
            decls.extend((path, d) for d in parsed[key])
        aliases = {d['address']: d['name'] for _, d in decls if d['address']}
        # An ASM claim may have only an address until its owner recovers a signature.
        # Its numeric symbol can still resolve a declaration, without proving source status.
        targets = [(f['addr'], f.get('symbol') or 'func_%08X' % f['addr'],
                    f.get('status') == 'source') for f in u['functions']]
        targets += [(addr, sym, False) for sym, addr in u['externs'].items()]
        targets += [(d['address'], d['name'], False) for _, d in decls if d['address']]
        for addr, symbol, matched in targets:
            if matched_only and not matched:
                continue
            method_name = demangle_method(symbol)
            names = {symbol, aliases.get(addr), method_name, symbol.split('__F')[0]}
            candidates = [(p, d) for p, d in decls if d['name'] in names or d['qualified_name'] in names]
            if method_name:
                # The spelling above does not decode overload argument types. Do not
                # let declaration order choose a signature for an overloaded name.
                signatures = set()
                for _, declaration in candidates:
                    params = list(declaration['params'])
                    if declaration['implicit_this']:
                        params[0] = ('void *', method_name.rsplit('::', 1)[0])
                    signatures.add((declaration['ret'], tuple(params)))
                if len(signatures) > 1:
                    evidence.append(dict(addr=addr, kind='source-overload-ambiguous', symbol=symbol))
                    continue
            # A definition resolves parameter names that the declaration omits.
            candidates.sort(key=lambda x: (bool(x[1]['body']), x[0] == u['source']), reverse=True)
            if not candidates:
                continue
            p, d = candidates[0]
            # Automatic drafts prove emitted behavior, but their scalar/pointer annotations
            # are lower-quality than an authored signature or field-use evidence.
            quality = 4 if matched and not (u.get('origin') == 'auto' or 'auto/' in u['source']) else (1.5 if matched else 1.75)
            s = dict(d, source=p, matched=matched, quality=quality, symbol=symbol,
                     this_usage=bool(d.get('implicit_this') or re.search(r'\(\s*[^,]*\b(this|self)\b', d['raw'])))
            previous = seeds.get(addr)
            if previous and (previous['ret'], previous['params']) != (s['ret'], s['params']):
                evidence.append(dict(addr=addr, kind='source-conflict', signatures=[previous['raw'], s['raw']]))
            if not previous or s['quality'] > previous['quality']:
                seeds[addr] = s
    return seeds, evidence


@dataclass(frozen=True)
class Value:
    """Origins survive register aliases; a displacement is retained only when constant."""
    origins: frozenset = frozenset()       # arg(slot,offset), ret(callee,0), field((slot,parent),pointee_offset)
    types: frozenset = frozenset()


def join_value(a, b):
    origins = a.origins | b.origins
    # A widened value is unknown, not whichever eight origins happened to arrive first.
    return Value(frozenset({('unknown', 0, 0)}) if ('unknown', 0, 0) in origins or len(origins) > 8 else origins, a.types | b.types)


def shift_value(v, off):
    return Value(frozenset((k, n, delta + off if k != 'unknown' else delta) for k, n, delta in v.origins), v.types)


def initial_state():
    s = [Value() for _ in range(64)]
    for k in range(8):
        s[4 + k] = Value(frozenset({('arg', k, 0)}))
        s[32 + 12 + k] = Value(frozenset({('farg', k, 0)}))
    s[29] = Value(frozenset({('stack', 0, 0)}), frozenset({'void *'}))
    return tuple(s)


def effects(x):
    reads, writes = set(), set()
    w = x.getRaw()
    for flag, reg in [('Rs', w >> 21 & 31), ('Rt', w >> 16 & 31), ('Rd', w >> 11 & 31),
                      ('Fs', 32 + (w >> 11 & 31)), ('Ft', 32 + (w >> 16 & 31)), ('Fd', 32 + (w >> 6 & 31))]:
        if getattr(x, 'reads' + flag)():
            reads.add(reg)
        if getattr(x, 'modifies' + flag)():
            writes.add(reg)
    return reads, writes


def instruction_value(x, state, reads):
    w, op = x.getRaw(), x.getOpcodeName()
    rs, rt, rd, fs, ft = w >> 21 & 31, w >> 16 & 31, w >> 11 & 31, 32 + (w >> 11 & 31), 32 + (w >> 16 & 31)
    imm = (w & 0xffff) - (0x10000 if w & 0x8000 else 0)
    if op in ('addu', 'daddu', 'or', 'por') and (rs == 0 or rt == 0):
        return state[rt if rs == 0 else rs] if rs or rt else Value(types=frozenset({'s32'}))
    if op in ('addiu', 'daddiu'):
        return shift_value(state[rs], imm) if rs else Value(types=frozenset({'s32'}))
    if op in ('mov.s', 'mov.d'):
        return state[fs]
    if op == 'mtc1':
        return Value(state[rt].origins, frozenset({'f32'}))
    if op == 'mfc1':
        return Value(state[fs].origins, frozenset({'s32'}))
    if x.doesLoad():
        origins = frozenset(('field', (n, off + imm), 0) for kind, n, off in state[rs].origins if kind == 'arg' and op in ('lw', 'lwu'))
        origins |= frozenset(('pointee', n, off + imm) for kind, n, off in state[rs].origins if kind == 'field' and op in ('lw', 'lwu'))
        return Value(origins, frozenset({MEMORY[op][0]}) if op in MEMORY else frozenset())
    if op.startswith(('p', 'qmfc2')) and op != 'pref':
        return Value(types=frozenset({'s128'}))
    if op.endswith('.s'):
        return Value(types=frozenset({'f32'}))
    if op.endswith('.d'):
        return Value(types=frozenset({'f64'}))
    if op.startswith(('dadd', 'dsub', 'dsll', 'dsrl', 'dsra')):
        return Value(types=frozenset({'s64'}))
    if writes_integer(op):
        return Value(types=frozenset({'s32'}))
    return Value()


def writes_integer(op):
    return op in ('add', 'addi', 'addu', 'addiu', 'sub', 'subu', 'and', 'andi', 'or', 'ori', 'xor', 'xori',
                  'nor', 'sll', 'srl', 'sra', 'sllv', 'srlv', 'srav', 'slt', 'sltu', 'slti', 'sltiu', 'lui', 'mflo', 'mfhi')


def variadic_register_saves(f):
    """Recognize SN's varargs home area, not ordinary argument uses.

    Require a contiguous suffix of incoming GPRs and the complete even FP bank
    in disjoint, consecutive stack slots before any control transfer. A lone
    spill or a normal callee-save prologue is insufficient evidence.
    """
    import rabbitizer
    gpr, fp, written = {}, {}, set()
    for pc, word in enumerate(f['words'][:48]):
        ins = rabbitizer.Instruction(word, f['addr'] + 4*pc, rabbitizer.InstrCategory.R5900)
        if ins.isBranch() or ins.isJump() or ins.isFunctionCall():
            break
        op = ins.getOpcodeName()
        rs, rt = word >> 21 & 31, word >> 16 & 31
        offset = (word & 0xffff) - (0x10000 if word & 0x8000 else 0)
        if op == 'sd' and rs == 29 and 5 <= rt <= 11 and rt not in written:
            gpr[rt] = (pc, offset)
        if op == 'swc1' and rs == 29 and rt in (12, 14, 16, 18) and 32 + rt not in written:
            fp[rt] = (pc, offset)
        written.update(effects(ins)[1])
    if len(gpr) < 2 or set(gpr) != set(range(min(gpr), 12)) or set(fp) != {12, 14, 16, 18}:
        return None
    go = [gpr[k][1] for k in sorted(gpr)]
    fo = [fp[k][1] for k in sorted(fp)]
    if go != list(range(go[0], go[0] + 8*len(go), 8)) or fo != list(range(fo[0], fo[0] + 16, 4)):
        return None
    if go[0] % 8 or fo[0] % 4 or max(fo) + 4 > min(go):
        return None
    return dict(fixed_gpr=min(gpr) - 4,
                saves={pc: reg for reg, (pc, _) in gpr.items()} |
                      {pc: 32 + reg for reg, (pc, _) in fp.items()})


def analyze_function(f):
    """Forward fixpoint with branch joins, executed delay slots and caller clobbers.

    Returns symbolic call-site values, incoming use constraints and field accesses.
    Saved-register stores do not imply an argument width. Unknown indirect calls clobber
    caller registers but never seed unrelated functions with made-up signatures.
    """
    import rabbitizer
    ins = [rabbitizer.Instruction(w, f['addr'] + 4*i, rabbitizer.InstrCategory.R5900) for i, w in enumerate(f['words'])]
    incoming, queue = {0: initial_state()}, collections.deque([0])
    uses, fields, calls, returns, nested = set(), set(), {}, set(), set()
    return_consumers = set()
    varargs = variadic_register_saves(f)

    def constrain(v, typ, pc):
        for kind, n, off in v.origins:
            if kind in ('arg', 'farg', 'ret'):
                uses.add((kind, n, typ, pc))

    def step(i, state):
        x, old = ins[i], state
        op, w = x.getOpcodeName(), x.getRaw()
        reads, writes = effects(x)
        rs, rt, fs = w >> 21 & 31, w >> 16 & 31, 32 + (w >> 11 & 31)
        imm = (w & 0xffff) - (0x10000 if w & 0x8000 else 0)
        copy = op in ('addu', 'daddu', 'or', 'por') and (rs == 0 or rt == 0)
        return_copy = copy or op in ('mov.s', 'mov.d') or (op in ('addiu', 'daddiu') and imm == 0)
        for reg in reads:
            if varargs and varargs['saves'].get(i) == reg:
                continue             # va_start register homing is not a named argument
            constrain(old[reg], 'used', i)
            if not return_copy:
                for kind, callee, _ in old[reg].origins:
                    if kind == 'ret':
                        return_consumers.add((callee, 'fpr' if reg >= 32 else 'gpr', i))
        if op in MEMORY:
            typ, size = MEMORY[op]
            base = old[rs]
            constrain(base, 'void *', i)
            for kind, n, off in base.origins:
                if kind in ('arg', 'farg') and 0 <= off + imm < 0x10000:
                    fields.add((kind, n, off + imm, size, typ, i))
                elif kind == 'field':
                    slot, parent = n
                    if 0 <= parent < 0x10000:
                        fields.add(('arg', slot, parent, 4, 'void *', i))
                        nested.add((slot, parent, off + imm, size, typ, i))
                elif kind == 'pointee':
                    # A loaded element is itself a pointer: no scalar-pointee claim.
                    slot, parent = n
                    nested.add((slot, parent, None, 0, 'nested-pointer', i))
            # VU register numbers are a separate bank, not aliases of GPRs.
            if x.doesStore() and rs != 29 and op != 'sqc2':
                constrain(old[rt if op not in ('swc1',) else ft_register(w)], typ, i)
        if op.startswith('p') and op != 'pref' and not (op == 'por' and (rs == 0 or rt == 0)):
            for reg in reads:
                constrain(old[reg], 's128', i)
        if op.startswith(('dsll32', 'dsrl32', 'dsra32')):
            for reg in reads:
                constrain(old[reg], 's64', i)
        if op.endswith('.s'):
            for reg in reads:
                if reg >= 32:
                    constrain(old[reg], 'f32', i)
        if writes and op not in MEMORY and not copy and op not in ('addiu', 'daddiu'):
            # Unknown indexed arithmetic/escapes must not disappear while retaining
            # only the easy zero-displacement accesses for the same pointer field.
            for reg in reads:
                for kind, identity, off in old[reg].origins:
                    if kind == 'field':
                        slot, parent = identity
                        nested.add((slot, parent, None, 0, 'unknown-use', i))
        if op in ('addiu', 'daddiu') and imm:
            # Preserve uncertainty even if a loop later widens away the precise
            # displaced origins before its next dereference.
            for kind, identity, displacement in old[rs].origins:
                if kind == 'field':
                    slot, parent = identity
                    nested.add((slot, parent, displacement + imm, 0, 'pointer-arithmetic', i))
        if op == 'mtc1':
            # Bit transfer alone does not prove the source is a C float argument.
            pass
        value = instruction_value(x, old, reads)
        new = list(old)
        for reg in writes:
            if reg:
                new[reg] = value
        return tuple(new)

    def emit_call(i, state, tail=False):
        rel = f['rel'].get(str(i))
        dest = rel[1] if rel and rel[0] == 'jal' and isinstance(rel[1], int) and not rel[2] else None
        vals = tuple(state[4:12]) + tuple(state[44:52])
        key = (i, dest, tail)
        if key in calls:
            vals = tuple(join_value(a, b) for a, b in zip(calls[key], vals))
        calls[key] = vals
        new = list(state)
        # t0..t7, a0..a3, at/v, fp temporaries and return registers are volatile.
        for reg in list(range(1, 16)) + [24, 25] + list(range(32, 52)):
            new[reg] = Value()
        if dest is not None:
            new[2] = new[32] = Value(frozenset({('ret', dest, 0)}))
        return tuple(new)

    def push(index, state):
        if not 0 <= index < len(ins):
            return
        previous = incoming.get(index)
        merged = state if previous is None else tuple(join_value(a, b) for a, b in zip(previous, state))
        if previous != merged:
            incoming[index] = merged
            queue.append(index)

    while queue:
        i = queue.popleft()
        x, state = ins[i], incoming[i]
        op = x.getOpcodeName()
        control = x.isBranch() or x.isJump() or x.isFunctionCall()
        if not control:
            push(i + 1, step(i, state))
            continue
        # jalr's target is read before the delay instruction, while outgoing arguments
        # are read by the callee after it. This ordering matters for common wrappers.
        before = step(i, state)
        delayed = step(i + 1, before) if i + 1 < len(ins) else before
        if x.isFunctionCall():
            push(i + 2, emit_call(i, delayed))
        elif x.isJrRa():
            returns.add((delayed[2], delayed[32]))
        elif x.isBranch():
            target = i + (x.getBranchOffsetGeneric() >> 2)
            push(target, delayed)
            if not x.isUnconditionalBranch():
                push(i + 2, before if x.isBranchLikely() else delayed)
        elif op == 'j':
            dest = ((f['addr'] + 4*i + 4) & 0xf0000000) | ((x.getRaw() & 0x3ffffff) << 2)
            if f['addr'] <= dest < f['addr'] + 4*len(ins):
                push((dest - f['addr']) // 4, delayed)
            else:
                emit_call(i, delayed, True)
        # Unresolved computed jumps end this path; never scan their unreachable tail linearly.
    return dict(uses=uses, fields=fields, calls=calls, returns=returns, nested=nested,
                return_consumers=return_consumers, syscall=any(x.getOpcodeName() == 'syscall' for x in ins))


def ft_register(w):
    return 32 + (w >> 16 & 31)


def resolve_type(candidates):
    """Resolve compatible width/signedness; preserve actual incompatible evidence."""
    c = set(candidates) - {'used', 'unknown', '...'}
    if not c:
        return 'unknown', []
    if len(c) == 1:
        return next(iter(c)), []
    pointers = {t for t in c if '*' in t}
    scalars = c - pointers
    concrete = pointers - {'void *'}
    if pointers and scalars <= {'s32', 'u32'} and len(concrete) <= 1:
        return next(iter(concrete)) if concrete else 'void *', []
    # int operations often consume only the low word of a pointer; pointer-vs-int
    # does not prove an incompatible ABI, but 64 and 128 or float/int do.
    if c <= {'s32', 'u32', 'void *'}:
        return ('void *' if 'void *' in c else 's32'), []
    widths = {WIDTH.get(t) for t in c}
    if len(widths) == 1 and all(t[0] in 'su' and t[1:].isdigit() for t in c):
        return 's' + str(next(iter(widths))*8), []
    return 'unknown', sorted(c)


def abi_slots(params):
    """SN EE has independent a0..a7 and f12..f19 argument banks.

    Original parameter ordering is preserved for source signatures. Without a source
    signature, integer-then-float ordering describes the same register ABI; the original
    mixed ordering remains unknown. Wider integers occupy one 128-bit GPR slot.
    SN's software double uses the integer bank, as confirmed by a worker probe.
    """
    gpr, fpr, stack, out = 0, 0, 0, []
    for typ, _ in params:
        if typ == '...':
            break
        if typ == 'f32':
            slot, fpr = 8 + fpr, fpr + 1
        else:
            slot, gpr = gpr, gpr + 1
        if (typ == 'f32' and fpr > 8) or (typ != 'f32' and gpr > 8):
            slot, stack = 16 + stack, stack + 1
        out.append((slot, typ))
    return out


def ghidra_seeds(root=ROOT):
    out = {}
    p = root / '.local/ghidra/functions_named.json'
    if not p.exists():
        return out
    for f in json.loads(p.read_text()).get('functions', []):
        if f.get('isThunk') or f.get('isDefaultName') or f['returnType'] == 'undefined':
            continue
        ps = [normalize_type(x['dataType'], True) for x in f.get('parameters', [])]
        ret, cls = normalize_type(f['returnType'], True)
        out[int(f['address'], 16)] = dict(name=f['name'], params=ps, ret=ret, retclass=cls, cls=None,
                                        quality=1, matched=False, raw=f['signature'], source='ghidra',
                                        this_usage=bool(f.get('parameters') and f['parameters'][0].get('name') in ('this', 'self')))
    return out


def closed_leaf(f):
    """A small straight-line leaf whose live argument registers are fully observed.

    This proves the minimum machine ABI, not the number of unused C parameters.
    Do not infer it through calls, branches, system/VU/MMI operations or raw words.
    """
    import rabbitizer
    words = f['words']
    if not 2 <= len(words) <= 32 or words[-2] != 0x03e00008:
        return False
    allowed = set(MEMORY) - {'lqc2', 'sqc2'}
    allowed |= {'nop', 'jr', 'addu', 'daddu', 'addiu', 'daddiu', 'subu', 'dsubu', 'and', 'andi',
                'or', 'ori', 'xor', 'xori', 'nor', 'sll', 'srl', 'sra', 'sllv', 'srlv', 'srav',
                'slt', 'sltu', 'slti', 'sltiu', 'lui', 'mov.s', 'add.s', 'sub.s', 'mul.s',
                'neg.s', 'abs.s', 'mtc1', 'mfc1', 'cvt.s.w', 'cvt.w.s', 'trunc.w.s'}
    for index, word in enumerate(words):
        op = rabbitizer.Instruction(word, f['addr'] + 4*index, rabbitizer.InstrCategory.R5900).getOpcodeName()
        if op not in allowed or op == 'jr' and index != len(words) - 2:
            return False
    return True


def recover_signatures(inv, analysis, seeds):
    """Whole-callgraph constraints with separate EE integer/floating argument banks."""
    constraints = collections.defaultdict(set)
    register_slots, caller_counts = {}, collections.defaultdict(collections.Counter)
    authoritative = {}
    variadic = {f['addr']: saves for f in inv if (saves := variadic_register_saves(f))
                and not (seeds.get(f['addr'], {}).get('quality', 0) >= 2
                         and not any(t == '...' for t, _ in seeds[f['addr']]['params']))}
    for addr, seed in seeds.items():
        if any(typ == '...' for typ, _ in seed['params']) and seed['quality'] >= 2:
            variadic[addr] = dict(fixed_gpr=None, saves={})
    observed_returns = collections.defaultdict(set)
    return_consumers = collections.defaultdict(set)
    direct_returns, live_slots = {}, {}
    # Inline syscall stubs can byte-match a void(void) definition while consuming
    # implicit syscall arguments. That source signature is not ABI evidence.
    surface_seeds = seeds
    seeds = {a: s for a, s in seeds.items() if not s.get('abi_uncertainty') and not (not s['params'] and 'syscall' in s.get('body', ''))}
    leaf_minima = {f['addr'] for f in inv if closed_leaf(f) and not analysis[f['addr']]['calls']
                   and any(kind in ('arg', 'farg') for kind, _, _, _ in analysis[f['addr']]['uses'])}
    for f in inv:
        a, result = f['addr'], analysis[f['addr']]
        direct_returns[a] = {bank: sorted({typ for values in result['returns'] for typ in values[index].types})
                             for index, bank in enumerate(('gpr', 'fpr'))}
        for callee, bank, pc in result.get('return_consumers', []):
            return_consumers[callee].add((a, bank, pc))
        used = set()
        for kind, k, typ, pc in result['uses']:
            if kind == 'ret':
                if typ != 'used':
                    observed_returns[k].add(typ)
                    constraints[(k, 'ret', 0)].add(typ)
                continue
            slot = k + (8 if kind == 'farg' else 0)
            used.add(slot)
            if kind == 'farg' or typ != 'f32':
                constraints[(a, 'arg', slot)].add(typ)
        ng = max((k+1 for k in used if k < 8), default=0)
        nf = max((k-7 for k in used if k >= 8), default=0)
        register_slots[a] = list(range(ng)) + list(range(8, 8+nf))
        live_slots[a] = sorted(used)
        if a in variadic and variadic[a]['fixed_gpr'] is not None:
            register_slots[a] = list(range(variadic[a]['fixed_gpr'])) + list(range(8, 8+nf))
        for (pc, dest, tail), values in result['calls'].items():
            if dest is None:
                continue
            defined = [k for k, v in enumerate(values) if v.types and not any(o[0] in ('arg', 'farg') for o in v.origins)]
            if defined:
                g = max((k+1 for k in defined if k < 8), default=0)
                fp = max((k-7 for k in defined if k >= 8), default=0)
                caller_counts[dest][(g, fp)] += 1
    for a, counter in caller_counts.items():
        if a in leaf_minima or a in variadic:
            continue                 # caller temporaries do not become unused leaf arguments
        g, fp = max(counter, key=lambda key: (counter[key], -sum(key)))
        slots = register_slots.get(a, [])
        g = max(g, max((k+1 for k in slots if k < 8), default=0))
        fp = max(fp, max((k-7 for k in slots if k >= 8), default=0))
        register_slots[a] = list(range(g)) + list(range(8, 8+fp))
    for a, seed in seeds.items():
        mapped = abi_slots(seed['params'])
        if seed['quality'] >= 2:
            register_slots[a] = [slot for slot, _ in mapped]
        elif a not in variadic and (a not in leaf_minima or seed['quality'] > 1.5):
            register_slots[a] = sorted(set(register_slots.get(a, [])) | {slot for slot, _ in mapped})
        for slot, typ in mapped:
            if typ != 'unknown':
                constraints[(a, 'arg', slot)].add(typ)
                if seed['quality'] >= 2:
                    authoritative[(a, 'arg', slot)] = typ
        # Unmatched source and automatic draft return annotations are hints. Do
        # not mix a wrong draft's s32 into an observed f0 result's f32 constraint.
        if seed['quality'] >= 2:
            constraints[(a, 'ret', 0)].add(seed['ret'])
        if seed['quality'] >= 2 and seed['ret'] != 'unknown':
            authoritative[(a, 'ret', 0)] = seed['ret']
    # An lq/sq initialization can leave a vector temporary in v0 on exit.
    # Its physical width alone does not prove a 128-bit return. Track actual
    # demand backward through forwarding wrappers; a live callee must not make
    # an otherwise unused wrapper's leftover return register authoritative.
    gpr_demand = {a for a, consumers in return_consumers.items()
                  if any(bank == 'gpr' for _, bank, _ in consumers)}
    gpr_demand |= {a for a, seed in seeds.items() if seed['quality'] >= 2
                   and seed['ret'] not in ('unknown', 'void', 'f32')}
    forwarded = collections.defaultdict(set)
    for f in inv:
        a, result = f['addr'], analysis[f['addr']]
        for gpr, _ in result['returns']:
            forwarded[a].update(n for kind, n, off in gpr.origins
                                if kind == 'ret' and not off)
        for (_, dest, tail), values in result['calls'].items():
            if dest is None:
                continue
            if tail:
                forwarded[a].add(dest)
            target = seeds.get(dest)
            if target and target['quality'] >= 2:
                for slot, typ in abi_slots(target['params']):
                    if slot < 8 and slot < len(values) and typ in ('s128', 'u128', 's64', 'u64', 'f64'):
                        gpr_demand.update(n for kind, n, off in values[slot].origins
                                          if kind == 'ret' and not off)
    demand_queue = collections.deque(gpr_demand)
    while demand_queue:
        for callee in forwarded[demand_queue.popleft()] - gpr_demand:
            gpr_demand.add(callee)
            demand_queue.append(callee)
    links, fixed = set(), collections.defaultdict(set)
    for f in inv:
        a, result = f['addr'], analysis[f['addr']]
        for (pc, dest, tail), values in result['calls'].items():
            if dest is None:
                continue
            for slot in register_slots.get(dest, []):
                if slot >= len(values):
                    continue                 # stack arguments remain explicit limitations
                value, key = values[slot], (dest, 'arg', slot)
                fixed[key] |= value.types
                for kind, n, off in value.origins:
                    if off:
                        continue
                    if kind in ('arg', 'farg'):
                        links.add((key, (a, 'arg', n + (8 if kind == 'farg' else 0))))
                    elif kind == 'ret':
                        links.add((key, (n, 'ret', 0)))
            if tail:
                links.add(((a, 'ret', 0), (dest, 'ret', 0)))
        seed = seeds.get(a)
        observed_ret, _ = resolve_type(observed_returns[a])
        known_ret = seed['ret'] if seed and seed['quality'] >= 2 else (observed_ret if observed_ret != 'unknown' else None)
        for gpr, fpr in result['returns']:
            banks = [fpr] if known_ret == 'f32' else [gpr] if known_ret and known_ret != 'unknown' else ([gpr] if gpr.origins or gpr.types else [fpr])
            for value in banks:
                fixed[(a, 'ret', 0)] |= {typ for typ in value.types
                    if typ not in ('s128', 'u128') or a in gpr_demand}
                for kind, n, off in value.origins:
                    if kind == 'ret' and not off:
                        links.add(((a, 'ret', 0), (n, 'ret', 0)))
                    elif kind in ('arg', 'farg') and not off:
                        links.add(((a, 'ret', 0), (a, 'arg', n + (8 if kind == 'farg' else 0))))
    for key, values in fixed.items():
        constraints[key] |= values
    # Never flood every conflicting observation through generic API arguments.
    adjacency = collections.defaultdict(set)
    for a, b in links:
        adjacency[a].add(b)
        adjacency[b].add(a)
    queue, sent = collections.deque(constraints), set()
    while queue:
        key = queue.popleft()
        typ = authoritative.get(key) or resolve_type(constraints[key])[0]
        if typ in ('s128', 'u128') and key[1] == 'ret' and key[0] not in gpr_demand:
            continue
        scalar_return = key[1] == 'ret' and typ in ('s32', 'u32')
        if (not scalar_return and typ not in ('void *', 'f32', 'f64', 's64', 'u64', 's128', 'u128') and '*' not in typ) or (key, typ) in sent:
            continue
        sent.add((key, typ))
        for other in adjacency[key]:
            if typ in ('s128', 'u128') and other[1] == 'ret' and other[0] not in gpr_demand:
                continue
            if scalar_return and other[1] != 'ret':
                continue             # exact returned copies, not generic API arguments
            if other not in authoritative and typ not in constraints[other]:
                constraints[other].add(typ)
                queue.append(other)
    out = {}
    for f in inv:
        a, seed = f['addr'], seeds.get(f['addr'])
        slots = register_slots.get(a, [])
        leaf_minimum = a in leaf_minima and not (seed and seed['quality'] >= 2)
        row = dict(name=f['name'], arity=len(slots) if slots or leaf_minimum or seed and seed['quality'] >= 2 else None,
                   register_slots=slots, arity_kind='signature' if seed and seed['quality'] >= 2 else
                   ('closed-leaf live minimum; unused parameters unknown' if leaf_minimum else 'lower-bound+caller-mode; mixed order unknown'),
                   caller_counts={'g%d/f%d' % key: n for key, n in caller_counts[a].items()},
                   params=[], ret='unknown', conflicts=[], classes={}, this=bool(seed and seed.get('this_usage', seed.get('cls'))),
                   source=seed['source'] if seed else None, source_quality=seed['quality'] if seed else 0,
                   surface_abi_ambiguity=surface_seeds.get(a, {}).get('abi_uncertainty', []),
                   ret_class=seed.get('retclass') if seed else None)
        row['live_register_slots'] = live_slots[a]
        row['syscall'] = analysis[a].get('syscall', False)
        row['return_evidence'] = dict(direct_types=direct_returns[a],
                                     consumed_banks=sorted({bank for _, bank, _ in return_consumers[a]}),
                                     consumers=len(return_consumers[a]), gpr_demand=a in gpr_demand)
        if a in variadic:
            row['variadic'] = True
            row['arity_kind'] = 'variadic signature' if seed and seed['quality'] >= 2 else 'SN variadic register-save ABI'
        for ordinal, slot in enumerate(slots):
            key = (a, 'arg', slot)
            typ, conflict = resolve_type(constraints[key])
            typ = authoritative.get(key) or typ
            if typ == 'unknown' and slot >= 8:
                typ = 'f32'          # a used floating ABI register is never a GPR parameter
            row['params'].append(typ)
            if conflict:
                row['conflicts'].append(dict(slot=ordinal, register=slot, types=conflict))
            if seed and seed['quality'] >= 2 and ordinal < len(seed['params']) and seed['params'][ordinal][1]:
                row['classes'][str(ordinal)] = [seed['params'][ordinal][1]]
        row['ret'], conflict = resolve_type(constraints[(a, 'ret', 0)])
        row['ret'] = authoritative.get((a, 'ret', 0)) or row['ret']
        if seed and seed['quality'] < 2:
            hint = seed['ret']
            row['return_hint'] = hint
            facts = constraints[(a, 'ret', 0)] - {'used', 'unknown', 'void'}
            if (not facts and hint not in ('unknown', 'void')
                    and (hint not in ('s128', 'u128') or a in gpr_demand)):
                row['ret'] = hint
            elif row['ret'] != 'unknown' and hint not in ('unknown', 'void', row['ret']):
                compatible, incompatible = resolve_type({hint, row['ret']})
                if incompatible:
                    row['conflicts'].append(dict(slot='ret', kind='source-hint-disagrees', types=incompatible))
                else:
                    # Preserve useful pointee hints when machine facts only prove
                    # a low-word/pointer ABI; incompatible float/int hints never win.
                    row['ret'] = compatible
        if conflict:
            row['conflicts'].append(dict(slot='ret', types=conflict))
        out[a] = row
    return out, links


def vtable_groups(inv, root=ROOT):
    from elfinfo import Elf
    boots = list((root / 'orig/usa-retail/files').glob('SLUS*'))
    if not boots:
        return {}
    elf = Elf(boots[0].read_bytes())
    sec = elf.section('.data')
    data, methods = elf.content(sec), {f['addr'] for f in inv}
    out, o = {}, 0
    while o + 8 <= len(data):
        entries, k = [], o
        while k + 8 <= len(data):
            adjust, fn = struct.unpack_from('<II', data, k)
            if adjust or fn not in methods:
                break
            entries.append(fn)
            k += 8
        if len(entries) >= 3:
            out[sec['addr'] + o] = entries
            o = k
        else:
            o += 4
    return out


def layout_fields(fields):
    """Only non-overlapping, consistently typed intervals become named fields.

    Signedness differences are compatible. Union/packed aliases remain byte arrays;
    the evidence still records every access so an agent can recover the real union.
    """
    byoff = collections.defaultdict(list)
    for off, size, typ, fn, pc in fields:
        byoff[off].append((size, typ, fn, pc))
    result = []
    intervals = [(off, off + size) for off, rows in byoff.items() for size, _, _, _ in rows]
    for off, rows in sorted(byoff.items()):
        sizes = {r[0] for r in rows}
        typ, conflict = resolve_type(r[1] for r in rows)
        overlap = any(lo != off and lo < off + max(sizes) and hi > off for lo, hi in intervals)
        if len(sizes) != 1 or conflict or overlap or typ == 'unknown' or off % max(sizes):
            continue
        result.append(dict(offset=off, size=next(iter(sizes)), type=typ,
                           functions=sorted({r[2] for r in rows})))
    return result


def refine_scalar_pointees(fields, nested):
    """Refine a pointer only from consistent, zero-displacement scalar accesses.

    Nested rows are (parent offset, pointee displacement, width, scalar type,
    function, instruction). The pointer's parent-field identity never changes
    when its loaded value is incremented. Nonzero/unknown accesses, pointer
    chasing and conflicting interpretations leave the parent as void*.
    """
    by_parent = collections.defaultdict(list)
    for parent, displacement, size, typ, function, pc in nested:
        by_parent[parent].append((displacement, size, typ, function, pc))
    out = []
    for original in fields:
        field = dict(original)
        rows = by_parent[field['offset']]
        if field['type'] == 'void *' and rows:
            scalar, conflict = resolve_type(row[2] for row in rows)
            valid = scalar in WIDTH and scalar != 'void *' and not conflict
            valid = valid and all(row[0] == 0 and row[1] == WIDTH[scalar] for row in rows)
            if valid:
                field['type'] = scalar + ' *'
                field['pointee_accesses'] = len(rows)
        out.append(field)
    return out


def recover_layouts(inv, analysis, seeds, signatures, root=ROOT):
    groups, membership = collections.defaultdict(set), collections.defaultdict(set)
    for a, s in seeds.items():
        for k, ((typ, cls), (slot, _)) in enumerate(zip(s['params'], abi_slots(s['params']))):
            if cls and slot < 8:
                cls = cls.removeprefix('Recovered_')
                membership[(a, slot)].add(cls)
                groups[cls].add((a, slot))
    vtables = vtable_groups(inv, root)
    # A method present in several vtables could be inherited; do not transitively merge
    # those classes or assert the base and derived layouts have identical extents.
    table_members = collections.defaultdict(set)
    for table, methods in vtables.items():
        for a in methods:
            table_members[a].add(table)
    for table, methods in vtables.items():
        name = 'Vtable_%08X' % table
        for a in methods:
            if len(table_members[a]) == 1 and not membership[(a, 0)]:
                groups[name].add((a, 0))
                membership[(a, 0)].add(name)
    # Same named class is the shared identity; mere calls to generic void* APIs do
    # not merge unrelated object arguments into one enormous invented structure.
    out = {}
    for name, nodes in sorted(groups.items()):
        fields, nested = [], []
        for a, k in nodes:
            for kind, slot, off, size, typ, pc in analysis.get(a, {}).get('fields', []):
                if kind == 'arg' and slot == k:
                    fields.append((off, size, typ, a, pc))
            for slot, parent, displacement, size, typ, pc in analysis.get(a, {}).get('nested', []):
                if slot == k:
                    nested.append((parent, displacement, size, typ, a, pc))
        if not fields:
            continue
        emitted = refine_scalar_pointees(layout_fields(fields), nested)
        if not emitted:
            continue
        ident = 'Recovered_' + re.sub(r'\W+', '_', name)
        out[ident] = dict(class_name=name, nodes=sorted(nodes), fields=emitted,
                          extent=max(o+s for o,s,_,_,_ in fields), allocation_size='unknown',
                          verified_by=[], nested_accesses=sorted(nested, key=repr), ambiguous_accesses=len(fields) - sum(len(x['functions']) for x in emitted))
    return out, vtables


def context_type(typ, m2c=False):
    if typ == 'unknown':
        return 's32'
    if m2c:
        return re.sub(r'\bu128\b', 'u64', re.sub(r'\bs128\b', 's64', typ))
    return typ


def prototype(row, m2c=False):
    ret = row.get('ret_view') or context_type(row['ret'], m2c)
    # Unknown arity is deliberately K&R, never a false zero-argument signature.
    params = ', '.join(row.get('param_views', {}).get(str(k), context_type(t, m2c)) for k, t in enumerate(row['params'])) if row['arity'] is not None else ''
    if row['arity'] == 0:
        params = 'void'
    if row.get('variadic') and row['arity']:
        params += ', ...'
    return '%s %s(%s);' % (ret, row['name'], params)


def generated_layout_text(name, layout, m2c=False):
    out, cursor = ['typedef struct %s {' % name], 0
    for field in layout['fields']:
        off, size = field['offset'], field['size']
        if off > cursor:
            out.append('    u8 opaque_%X[%d];' % (cursor, off - cursor))
        out.append('    %s field_%X; /* PS2 +0x%X */' % (context_type(field['type'], m2c), off, off))
        if m2c and size == 16:
            out.append('    u8 wide_tail_%X[8];' % off)
        cursor = off + size
    # Size is only the accessed prefix, not an allocation-size or inheritance claim.
    if layout['extent'] > cursor:
        out.append('    u8 opaque_%X[%d];' % (cursor, layout['extent'] - cursor))
    out.append('} %s;' % name)
    return out


def verified_layout_users(names, root=ROOT):
    """Require a member access in a matched body and that exact view's dependency.

    Count per function, not every function in a TU that mentions a type. Includes,
    opaque-pointer calls and a type-name mention alone prove no field layout.
    """
    from units import dependencies
    result = {name: set() for name in names}
    # ABI ranking may prefer an authored, still-unmatched declaration over an
    # exact automatic definition. Layout proof must inspect the matched body,
    # independently of that signature choice.
    seeds, _ = source_seeds(root, matched_only=True)
    paths = {}
    for address, seed in seeds.items():
        if not seed.get('matched') or not seed.get('body'):
            continue
        source = seed['source']
        if source not in paths:
            paths[source] = {str(p) for p in dependencies(source)}
        text = seed['raw'] + ' ' + seed['body']
        mentioned = set(re.findall(r'\bRecovered_\w+\b', text)) & set(names)
        for name in mentioned:
            if 'include/recovered/%s.h' % name not in paths[source]:
                continue
            variables = re.findall(r'\b' + re.escape(name) + r'\s*\*\s*(\w+)', text)
            direct = any(re.search(r'\b' + re.escape(v) + r'\s*->\s*field_[0-9A-F]+', seed['body']) for v in variables)
            cast = re.search(r'\(\s*\(\s*' + re.escape(name) + r'\s*\*\s*\)[^;]+?\)\s*->\s*field_', seed['body'])
            if direct or cast:
                result[name].add(address)
    return {name: sorted(users) for name, users in result.items()}


def fingerprint(root=ROOT):
    h = hashlib.sha256()
    paths = [Path(__file__), root / 'config/units.yaml', root / 'config/symbols.txt', root / 'build/usa-retail/placement.json']
    paths += sorted((root / 'src').rglob('*.[ch]')) + sorted((root / 'src').rglob('*.cpp'))
    paths += sorted((root / 'include').rglob('*.h')) + sorted((root / 'include').rglob('*.hpp'))
    paths += sorted((root / '.local/ghidra').glob('*.json'))
    paths += [root.parent / 'the counterpart map']
    paths += sorted((root.parent / 'an unpublished companion project').rglob('*.json'))
    paths += sorted((root.parent / 'an unpublished companion project').rglob('*.cpp'))
    for p in paths:
        if p.is_file() and 'include/recovered' not in p.as_posix():
            h.update(p.read_bytes())
    return h.hexdigest()


def recover(inv=None, root=ROOT, refresh=False):
    cache = root / 'build/auto/context.json'
    stamp = fingerprint(root)
    if not refresh and cache.exists():
        old = json.loads(cache.read_text())
        if old.get('fingerprint') == stamp and old.get('version') == VERSION:
            return old
    if inv is None:
        from autodecomp import load_inventory
        inv = load_inventory()
    print('context: analyze %d PS2 functions (including all sizes)' % len(inv), flush=True)
    analysis = {}
    for index, f in enumerate(inv):
        analysis[f['addr']] = analyze_function(f)
        if (index + 1) % 2000 == 0:
            print('context: analyzed %d/%d' % (index + 1, len(inv)), flush=True)
    seeds, conflicts = source_seeds(root)
    ghidra = ghidra_seeds(root)
    for a, s in ghidra.items():
        if a not in seeds:
            seeds[a] = s
        elif (s['ret'], s['params']) != (seeds[a]['ret'], seeds[a]['params']):
            conflicts.append(dict(addr=a, kind='ghidra-source-conflict', signatures=[s['raw'], seeds[a]['raw']]))
    signatures, links = recover_signatures(inv, analysis, seeds)
    layouts, vtables = recover_layouts(inv, analysis, seeds, signatures, root)
    views = collections.defaultdict(set)
    for name, layout in layouts.items():
        for node in layout['nodes']:
            views[tuple(node)].add(name)
    for row in signatures.values():
        cls = row.get('ret_class')
        view = 'Recovered_' + re.sub(r'\W+', '_', cls.removeprefix('Recovered_')) if cls else None
        if view in layouts:
            row['ret_view'] = view + ' *'
    for (a, k), names in views.items():
        row = signatures.get(a)
        if row and len(names) == 1 and k in row['register_slots']:
            ordinal = row['register_slots'].index(k)
            if row['params'][ordinal] == 'void *':
                row.setdefault('param_views', {})[str(ordinal)] = next(iter(names)) + ' *'
    # Counterpart identities are discovery leads only: Xbox offsets never enter a PS2 layout.
    counterpart = root.parent / 'the counterpart map'
    leads = {}
    parent_sources = collections.defaultdict(list)
    if counterpart.exists():
        for module in sorted((root.parent / 'an unpublished companion project').rglob('*.json')):
            try:
                config = json.loads(module.read_text())
            except (ValueError, OSError):
                continue
            cpp = module.with_suffix('.cpp')
            declarations = parse_declarations(cpp.read_text()) if cpp.exists() else []
            functions = config.get('functions', {})
            if not isinstance(functions, dict):
                continue
            for address, symbol in functions.items():
                if not isinstance(symbol, str):
                    continue
                match = re.match(r'\?([^@]+)@([^@]*)@@', symbol)
                name = ((match.group(2) + '::') if match and match.group(2) else '') + match.group(1) if match else symbol
                related = [d['raw'] for d in declarations if d['name'] == name]
                parent_sources[address.lower()].append(dict(module=module.relative_to(root.parent).as_posix(), name=name, signatures=related))
        for pair in json.loads(counterpart.read_text()).get('pairs', []):
            a = int(pair['ps2'], 16)
            leads.setdefault(str(a), []).append(dict(xbox=pair['xbox'], confidence=pair['confidence'], region=pair['region'],
                                                   source_leads=parent_sources.get(pair['xbox'].lower(), [])))
    has_views = any('recovered/Recovered_' in p.read_text() for p in (root / 'src').rglob('*') if p.suffix in ('.c', '.cpp', '.h', '.hpp'))
    if has_views:
        verified = verified_layout_users(layouts, root)
        for name, layout in layouts.items():
            layout['verified_by'] = verified[name]
    summary = dict(functions=len(inv), source_signatures=sum(bool(s.get('matched')) for s in seeds.values()),
                   ambiguous_cpp_signatures=sum(bool(s.get('abi_uncertainty')) for s in seeds.values()),
                   ghidra_signatures=len(ghidra), direct_calls=sum(sum(k[1] is not None for k in a['calls']) for a in analysis.values()),
                   indirect_calls=sum(sum(k[1] is None for k in a['calls']) for a in analysis.values()),
                   propagated_links=len(links), signatures_with_conflicts=sum(bool(s['conflicts']) for s in signatures.values()),
                   unknown_arities=sum(s['arity'] is None for s in signatures.values()),
                   typed_arguments=sum(t != 'unknown' for s in signatures.values() for t in s['params']),
                   typed_returns=sum(s['ret'] != 'unknown' for s in signatures.values()),
                   layouts=len(layouts), verified_layouts=sum(bool(v['verified_by']) for v in layouts.values()),
                   vtable_groups=len(vtables), counterpart_leads=len(leads), counterpart_source_leads=sum(bool(x['source_leads']) for rows in leads.values() for x in rows))
    result = dict(version=VERSION, fingerprint=stamp, summary=summary, signatures={str(k): v for k, v in signatures.items()},
                  source_conflicts=conflicts, layouts=layouts, counterpart_leads=leads,
                  vtables={str(k): v for k, v in vtables.items()})
    cache.parent.mkdir(parents=True, exist_ok=True)
    cache.write_text(json.dumps(result, indent=2) + '\n')
    return result


def write_outputs(result, root=ROOT):
    directory = root / 'include/recovered'
    directory.mkdir(exist_ok=True)
    names = set(result['layouts'])
    # Only remove files this generator owns, never a hand-authored shared header.
    for p in directory.glob('Recovered_*.h'):
        if p.stem not in names and p.read_text().startswith('/* Generated by tools/context_recovery.py.'):
            p.unlink()
    all_headers = ['/* Generated by tools/context_recovery.py. PS2 access views; extent is not allocation size. */',
                   '#ifndef RECOVERED_LAYOUTS_H', '#define RECOVERED_LAYOUTS_H']
    ctx = []
    for name, layout in sorted(result['layouts'].items()):
        status = 'VERIFIED access view by ' + ', '.join('0x%X' % a for a in layout['verified_by']) if layout['verified_by'] else 'UNVERIFIED access view'
        lines = ['/* Generated by tools/context_recovery.py. %s; allocation size unknown. */' % status,
                 '#ifndef %s_H' % name.upper(), '#define %s_H' % name.upper(), '#include "auto/prelude.h"', '']
        lines += generated_layout_text(name, layout)
        for f in layout['fields']:
            lines.append('typedef char assert_%s_%X[(((int)&((%s *)0)->field_%X) == %d) ? 1 : -1];' % (name, f['offset'], name, f['offset'], f['offset']))
        lines += ['#endif', '']
        (directory / (name + '.h')).write_text('\n'.join(lines))
        all_headers.append('#include "recovered/%s.h"' % name)
        ctx += generated_layout_text(name, layout, True)
    all_headers += ['#endif', '']
    (directory / 'layouts.h').write_text('\n'.join(all_headers))
    auto = root / 'build/auto'
    (auto / 'recovered_layouts.c').write_text('\n'.join(ctx) + '\n')
    compile_lines = ['/* Generated by tools/context_recovery.py. Constraints, not proof of source signatures. */',
                     '#ifndef RECOVERED_SIGNATURES_H', '#define RECOVERED_SIGNATURES_H', '#include "auto/prelude.h"', '#include "recovered/layouts.h"']
    for _, row in sorted(result['signatures'].items(), key=lambda kv: int(kv[0])):
        compile_lines.append('extern ' + prototype(row))
    compile_lines += ['#endif', '']
    (directory / 'signatures.h').write_text('\n'.join(compile_lines))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--refresh', action='store_true')
    ap.add_argument('--report', action='store_true', help='report cached recovery without rewriting headers')
    args = ap.parse_args()
    result = recover(refresh=args.refresh)
    if not args.report:
        write_outputs(result)
    print(json.dumps(result['summary'], indent=2))


if __name__ == '__main__':
    main()
