import math
if __name__ == '__main__':
    l = int(input())
    # Combination(l - 1, 11)
    ans = 1
    for i in range(l - 1, l - 12, -1):
        ans *= i
    for i in range(11, 0, -1):
        ans //= i
    print(ans)
