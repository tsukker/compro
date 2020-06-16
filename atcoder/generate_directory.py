#! python3

import os
import pathlib
import shutil
import string
import sys

if __name__ == '__main__':
    argc = len(sys.argv)
    assert argc >= 2
    contest_id = sys.argv[1]
    num_problem = 6
    if argc >= 3:
        num_problem = int(sys.argv[2])
    assert 1 <= num_problem and num_problem <= 26
    contest_dir = pathlib.Path(contest_id)
    os.makedirs(contest_dir, exist_ok=True)
    # Create files for each problem
    for ch in string.ascii_lowercase[:num_problem]:
        path = contest_dir / (ch + '.cc')
        if not os.path.exists(path):
            shutil.copy2('../template_atcoder.cc', path)
    # Create .vscode directory
    vsc_path = contest_dir / '.vscode'
    os.makedirs(vsc_path, exist_ok=True)
    files = ['launch.json', 'settings.json', 'tasks.json']
    for file in files:
        path = vsc_path / file
        if not os.path.exists(path):
            shutil.copy2(f'../_vscode/{file}', path)
