#! python3

import os
import pathlib
import string
import sys

from onlinejudge_command.main import main as oj_main

if __name__ == '__main__':
    contest_id = os.path.basename(os.getcwd())
    problem_prefix = contest_id.replace('-', '_')
    argc = len(sys.argv)
    if argc >= 2:
        problem_prefix = sys.argv[1]
    if problem_prefix[-1] != '_':
        problem_prefix += '_'
    sys.argv = [sys.argv[0], 'd', '-f', 3, '-d', 5, '-s', 7]
    for ch in string.ascii_lowercase:
        path = ch + '.cc'
        if not os.path.exists(path):
            continue
        sys.argv[3] = 'sample-%i.%e'
        sys.argv[5] = f'testcase/{ch}/'
        url = f'https://atcoder.jp/contests/{contest_id}/tasks/{problem_prefix}{ch}'
        sys.argv[7] = url
        oj_main()
