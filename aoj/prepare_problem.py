#! python3

import os
import shutil
import sys

from onlinejudge_command.main import main as oj_main

if __name__ == '__main__':
    argc = len(sys.argv)
    assert argc >= 2
    problem_id = sys.argv[1]
    sys.argv = [sys.argv[0], 'd', '-f', 3, '-d', 5, '-s', 7]
    for _ in range(1):
        path = problem_id + '.cc'
        if not os.path.exists(path):
            shutil.copy2('../../template_atcoder.cc', path)
        sys.argv[3] = 'sample-%i.%e'
        sys.argv[5] = f'testcase/{problem_id}/'
        url = f'http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id={problem_id}'
        sys.argv[7] = url
        oj_main()
