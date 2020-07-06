# Aizu Online Judge (AOJ)

- [Stable website](http://judge.u-aizu.ac.jp/onlinejudge/index.jsp)
- [New website (beta)](https://onlinejudge.u-aizu.ac.jp/home)
- [System Information](https://onlinejudge.u-aizu.ac.jp/system_info)

## Directory

- root/
  - [Problem Set Name]/
    - [problem_id].cc
  - ITP1/
    - ITP1_1_A.cc
    - testcase/
      - ITP1_1_A/
        - sample-1.in
        - sample-1.out

## Usage

```shell
cd aoj
python generate_directory.py <Problem Set Name>

cd <Problem Set Name>
python ../prepare_problem.py <Problem ID>
```
