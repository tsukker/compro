#! python3

import os
import pathlib
import shutil
import sys

if __name__ == '__main__':
    argc = len(sys.argv)
    assert argc >= 2
    contest_id = sys.argv[1]
    contest_dir = pathlib.Path(contest_id)
    os.makedirs(contest_dir, exist_ok=True)
    # Create .vscode directory
    vsc_path = contest_dir / '.vscode'
    os.makedirs(vsc_path, exist_ok=True)
    files = ['launch.json', 'settings.json', 'tasks.json']
    for source_dir in ['./_vscode/', '../_vscode/']:
        for file in files:
            source_path = pathlib.Path(source_dir) / file
            target_path = vsc_path / file
            if os.path.exists(source_path) and not os.path.exists(target_path):
                shutil.copy2(source_path, target_path)
