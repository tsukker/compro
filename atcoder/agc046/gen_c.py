import random

if __name__ == '__main__':
    slen = 300
    s = ''.join(map(str, [random.randint(0, 1) for _ in range(slen)]))
    k = 10**9
    print(f'{s} {k}')
