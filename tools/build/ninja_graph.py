"""Construct Ninja edges and their generated-file I/O contracts from the same dependency lists."""
import json
from pathlib import Path
import shlex
from graph_io import write_text, python_inputs


def escape(path):
    return str(path).replace('$','$$').replace(' ','$ ').replace(':','$:')


class Graph:
    def __init__(self, out):
        self.out = str(out)
        self.edges = []

    def add(self, name, command, outputs, inputs=(), implicit=(), depfile=None, generator=False, console=False):
        outputs = list(dict.fromkeys(map(str,outputs)))
        inputs = list(dict.fromkeys(map(str,inputs)))
        implicit = list(dict.fromkeys(map(str,implicit)))
        if command:
            implicit += python_inputs(command[0])
            implicit += ['tools/build/graph_io.py']
            io = self.out+'/io/'+name+'.json'
            data = dict(reads=sorted(set(inputs+implicit+[io])),writes=outputs,managed_outputs=[depfile] if depfile else [])
            write_text(io,json.dumps(data,sort_keys=True)+'\n')
            implicit.append(io)
        edge = dict(name=name, command=command, outputs=outputs, inputs=inputs,
                    implicit=sorted(set(implicit)-set(inputs)), depfile=depfile,
                    generator=generator, console=console)
        self.edges.append(edge)
        return edge

    def render(self):
        lines=[]
        for index,e in enumerate(self.edges):
            if e['command'] is None:
                lines += ['build %s: phony %s' % (' '.join(map(escape,e['outputs'])),' '.join(map(escape,e['inputs']+e['implicit'])))]
                continue
            rule='edge_'+e['name'].replace('/','_').replace('.','_')
            # An explicit variable keeps multi-output commands independent of $out.
            io=self.out+'/io/'+e['name']+'.json'
            lines += ['rule '+rule,
                      '  command = $py tools/build/graph_io.py check %s -- %s' % (escape(io),shlex.join(e['command']).replace('$','$$')),
                      '  description = '+e['name']]
            if e['depfile']:
                lines += ['  depfile = '+escape(e['depfile']), '  deps = gcc']
            if e['generator']:
                lines += ['  generator = 1']
            lines += ['  restat = 1']
            if e['console']:
                lines += ['  pool = console']
            output=escape(e['outputs'][0])
            if len(e['outputs'])>1:
                output+=' | '+' '.join(map(escape,e['outputs'][1:]))
            lines += ['build %s: %s %s' % (output,rule,' '.join(map(escape,e['inputs'])))+
                      (' | '+' '.join(map(escape,e['implicit'])) if e['implicit'] else '')]
        return '\n'.join(lines)+'\n'


if __name__=='__main__':
    import argparse
    argparse.ArgumentParser(description=__doc__).parse_args()
