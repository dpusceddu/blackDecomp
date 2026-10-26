"""Ninja clean/deletion recovery and detection of undeclared generated-file reads, without game files or SDKs."""
import json
import os
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path[:0]=[str(Path(__file__).resolve().parents[2]/'tools/build')]
from check_graph import validate
from ninja_graph import Graph
import prepare

ROOT=Path(__file__).resolve().parents[2]


class GraphContracts(unittest.TestCase):
    def test_split_recovers_a_preserved_wrapper_without_its_inventory(self):
        with tempfile.TemporaryDirectory() as directory:
            previous=Path.cwd()
            try:
                os.chdir(directory)
                b=Path('build/test');b.mkdir(parents=True)
                (b/'splat.yaml').write_text(json.dumps(dict(options=dict(asm_path='asm/test',data_path='data'),
                    segments=[dict(subsegments=[[0,'textbin','vutext']])])) )
                wrapper=Path('asm/test/data/vutext.s');wrapper.parent.mkdir(parents=True)
                wrapper.write_text('old wrapper')
                other=wrapper.with_name('unrelated.s');other.write_text('preserved')
                def split(*args,**kwargs):
                    # Model upstream textbin's intentional existing-file skip.
                    if not wrapper.exists():wrapper.write_text('regenerated')
                with patch.object(sys,'argv',['prepare.py','split','test']), \
                     patch.dict(os.environ,BLACK_NINJA_RECORD=str(b/'missing.json')), \
                     patch.object(prepare.runpy,'run_module',side_effect=split):
                    prepare.main()
                self.assertEqual(wrapper.read_text(),'regenerated')
                self.assertEqual(other.read_text(),'preserved')
            finally:os.chdir(previous)

    def test_missing_producer_and_duplicate_producer_are_errors(self):
        edge=dict(name='link',outputs=['build/test/linked.elf'],inputs=['build/test/placement.json'])
        problems,_=validate([edge])
        self.assertTrue(any('no producer' in p for p in problems))
        producer=dict(name='placement',outputs=['build/test/placement.json'],inputs=[])
        duplicate=dict(producer,name='second')
        problems,_=validate([edge,producer,duplicate])
        self.assertTrue(any('multiple producers' in p for p in problems))

    def test_contract_read_must_be_a_direct_ninja_dependency(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);contract='build/test/io/link.json'
            path=root/contract;path.parent.mkdir(parents=True)
            path.write_text(json.dumps(dict(reads=['build/test/placement.json'],writes=['build/test/linked.elf'])))
            producer=dict(name='placement',outputs=['build/test/placement.json',contract],inputs=[])
            link=dict(name='link',outputs=['build/test/linked.elf'],inputs=[contract])
            problems,_=validate([producer,link],root)
            self.assertTrue(any('undeclared generated read' in p for p in problems))
            link['inputs'].append('build/test/placement.json')
            self.assertEqual(validate([producer,link],root)[0],[])

    def test_actual_read_outside_contract_is_rejected(self):
        (ROOT/'build').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='graph-read-',dir=ROOT/'build') as folder:
            base=Path(folder).relative_to(ROOT)
            source=base/'input.json';source.write_text('{}')
            output=base/'output.json'
            tool=base/'reader.py';tool.write_text('from pathlib import Path\nPath(%r).write_text("untrusted")\nPath(%r).read_text()\n'%(str(output),str(source)))
            spec=base/'io.json';spec.write_text(json.dumps(dict(reads=[str(tool)],writes=[str(output)])))
            command=[sys.executable,'tools/build/graph_io.py','check',str(spec),'--',str(tool)]
            bad=subprocess.run(command,cwd=ROOT,capture_output=True,text=True)
            self.assertNotEqual(bad.returncode,0)
            self.assertIn('undeclared reads: '+str(source),bad.stderr)
            self.assertFalse(output.exists())
            spec.write_text(json.dumps(dict(reads=[str(tool),str(source)],writes=[str(output)])))
            good=subprocess.run(command,cwd=ROOT,capture_output=True,text=True)
            self.assertEqual(good.returncode,0,good.stderr)

    def test_ninja_clean_and_each_missing_output_rebuild_the_producer(self):
        (ROOT/'.local').mkdir(exist_ok=True);(ROOT/'build').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='graph-fixture-',dir=ROOT/'.local') as local, \
             tempfile.TemporaryDirectory(prefix='graph-fixture-',dir=ROOT/'build') as generated:
            local=Path(local).relative_to(ROOT);base=Path(generated).relative_to(ROOT)
            tool=local/'stage.py'
            tool.write_text('import sys\nfrom pathlib import Path\nimport json\n'
                'a=json.loads(sys.argv[1])\n'
                'data="".join(Path(p).read_text() for p in a["inputs"])\n'
                'for p in a["outputs"]: Path(p).write_text(data+"built")\n')
            graph=Graph(local)
            meta=[str(base/'placement.json'),str(base/'layout.json')]
            obj=[str(base/'unit.o'),str(base/'unit.o.json')]
            report=[str(base/'report.json')]
            for name,inputs,outputs in [('metadata',[],meta),('object',meta,obj),('report',obj,report)]:
                graph.add(name,[str(tool),json.dumps(dict(inputs=inputs,outputs=outputs))],outputs,inputs)
            manifest=local/'build.ninja'
            manifest.write_text('py = '+sys.executable+'\nbuilddir = '+str(local/'state')+'\n'+graph.render()+'default '+report[0]+'\n')
            def ninja(*args):
                r=subprocess.run(['ninja','-f',str(manifest),*args],cwd=ROOT,capture_output=True,text=True)
                self.assertEqual(r.returncode,0,r.stdout+r.stderr)
            ninja();ninja('-t','clean');ninja()
            for name in meta+obj+report:
                (ROOT/name).unlink();ninja()
                self.assertTrue((ROOT/name).is_file(),name)

    def test_real_configure_repairs_a_deleted_generated_manifest(self):
        # Use the production configure/recorder with synthetic preparation
        # inventories. No ELF or SDK is needed to test Ninja's load/clean path.
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);b='build/SLUS_213.76'
            for name in ('configure.py','tools/build/graph_io.py','tools/build/ninja_graph.py'):
                path=root/name;path.parent.mkdir(parents=True,exist_ok=True)
                shutil.copyfile(ROOT/name,path)
            (root/'config').mkdir()
            (root/'config/versions.json').write_text(json.dumps({'SLUS_213.76':{'boot':'SLUS_213.76'}}))
            game=root/'orig/SLUS_213.76/SLUS_213.76';game.parent.mkdir(parents=True)
            game.write_bytes(b'synthetic preflight fixture')
            writer=root/'tools/fixture.py'
            writer.write_text('import sys,json\nfrom pathlib import Path\n'
                'for name,text in json.loads(Path(sys.argv[1]).read_text()).items():\n'
                ' p=Path(name);p.parent.mkdir(parents=True,exist_ok=True);p.write_text(text)\n')
            (root/'tools/object.py').write_text('from pathlib import Path\n'
                'Path("build/SLUS_213.76/unit.o").write_text(Path("build/SLUS_213.76/layout.json").read_text())\n')
            manifest='rule unit\n  command = python3 tools/object.py\nbuild '+b+'/unit.o: unit '+b+'/layout.json\nbuild all: phony '+b+'/unit.o\ndefault all\n'
            for name in ('extract','boundaries','split','support','functions','owners','units','placement','inventory','graph'):
                outputs={b+'/layout.json':'{}'} if name=='extract' else {b+'/objects.ninja':manifest,b+'/leaf_graph.json':'[]'} if name=='graph' else {}
                payload='config/'+name+'.json';(root/payload).write_text(json.dumps(outputs))
                for path,text in outputs.items():
                    dest=root/path;dest.parent.mkdir(parents=True,exist_ok=True);dest.write_text(text)
                contract=b+'/prepare/'+name+'.json'
                dest=root/contract;dest.parent.mkdir(parents=True,exist_ok=True)
                dest.write_text(json.dumps(dict(command=['tools/fixture.py',payload],reads=[payload,'tools/fixture.py'],writes=[contract]+list(outputs))))
            def run(*command):
                result=subprocess.run(command,cwd=root,capture_output=True,text=True)
                self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            run(sys.executable,'configure.py');run('ninja')
            (root/b/'objects.ninja').unlink();run('ninja')
            self.assertTrue((root/b/'objects.ninja').exists())
            run('ninja','-t','clean');run('ninja')
            self.assertTrue((root/b/'unit.o').exists())

    def test_real_configure_rediscovers_renamed_sources(self):
        # Cached preparation records must not make a removed source a fatal
        # prerequisite before the split list can select its replacement.
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);b='build/SLUS_213.76'
            for name in ('configure.py','tools/build/graph_io.py','tools/build/ninja_graph.py'):
                path=root/name;path.parent.mkdir(parents=True,exist_ok=True)
                shutil.copyfile(ROOT/name,path)
            (root/'config').mkdir()
            (root/'config/versions.json').write_text(json.dumps({'SLUS_213.76':{'boot':'SLUS_213.76'}}))
            game=root/'orig/SLUS_213.76/SLUS_213.76';game.parent.mkdir(parents=True)
            game.write_bytes(b'synthetic preflight fixture')
            source=root/'src/unit.c';source.parent.mkdir()
            source.write_text('first source')
            selected=root/'config/source.json';selected.write_text(json.dumps('src/unit.c'))
            writer=root/'tools/fixture.py'
            writer.write_text('import sys,json\nfrom pathlib import Path\n'
                'stage=sys.argv[1]\nb="build/SLUS_213.76"\n'
                'if stage=="units":\n'
                ' source=json.loads(Path("config/source.json").read_text())\n'
                ' Path(source).read_text()\n'
                ' Path(b+"/units.json").write_text(json.dumps(source))\n'
                'if stage=="graph":\n'
                ' source=json.loads(Path(b+"/units.json").read_text())\n'
                ' manifest="rule unit\\n  command = python3 tools/object.py $in\\n"\n'
                ' manifest+="build "+b+"/unit.o: unit "+source+"\\nbuild all: phony "+b+"/unit.o\\ndefault all\\n"\n'
                ' Path(b+"/objects.ninja").write_text(manifest)\n'
                ' Path(b+"/leaf_graph.json").write_text("[]")\n')
            (root/'tools/object.py').write_text('import sys\nfrom pathlib import Path\n'
                'Path("build/SLUS_213.76/unit.o").write_text(Path(sys.argv[1]).read_text())\n')
            for name in ('extract','boundaries','split','support','functions','owners','units','placement','inventory','graph'):
                contract=b+'/prepare/'+name+'.json'
                reads=['tools/fixture.py']
                writes=[contract]
                if name=='units':reads+=['config/source.json','src/unit.c'];writes+=[b+'/units.json']
                if name=='graph':reads+=[b+'/units.json'];writes+=[b+'/objects.ninja',b+'/leaf_graph.json']
                dest=root/contract;dest.parent.mkdir(parents=True,exist_ok=True)
                dest.write_text(json.dumps(dict(command=['tools/fixture.py',name],reads=reads,writes=writes)))
            def run(*command):
                result=subprocess.run(command,cwd=root,capture_output=True,text=True)
                self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            run(sys.executable,'tools/fixture.py','units')
            run(sys.executable,'tools/fixture.py','graph')
            run(sys.executable,'configure.py');run('ninja')
            for name,explicit in (('src/unit.cpp',False),('src/renamed.cpp',True)):
                replacement=root/name;source.rename(replacement);source=replacement
                source.write_text(name)
                selected.write_text(json.dumps(name))
                if explicit:run(sys.executable,'configure.py')
                run('ninja')
                self.assertEqual((root/b/'unit.o').read_text(),name)
                inventory=json.loads((root/b/'prepare/units.json').read_text())
                self.assertIn(name,inventory['reads'])
                self.assertNotIn('src/unit.c',inventory['reads'])


if __name__=='__main__':unittest.main()
