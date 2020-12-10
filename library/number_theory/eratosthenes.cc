// Sieve of Eratosthenes

#include <deque>
#include <map>
#include <unordered_map>
#include <vector>

struct Prime {
  int max_check;
  int max_prime;
  int prime_number;
  std::vector<int> primes;
  std::map<int, int> prime_id;
  Prime() {};
  Prime(int m) {
    initialize(m);
  };
  void initialize(int m) {
    sieve(m);
    prime_number = (int)primes.size();
    max_check = m;
  }

  void sieve(int m) {
    max_prime = 2;
    std::deque<bool> is_prime(m+1, true);
    is_prime[0] = is_prime[1] = false;
    int i;
    for (i = 2; i <= m; ++i) {
      if (!is_prime[i]) {
        continue;
      }
      if (i * i > m) {
        break;
      }
      for (int j = i*2; j <= m; j += i) {
        is_prime[j] = false;
      }
      prime_id[i] = (int)primes.size();
      primes.push_back(i);
      max_prime = i;
    }
    for (int j = i; j <= m; ++j) {
      if (!is_prime[j]) {
        continue;
      }
      prime_id[j] = (int)primes.size();
      primes.push_back(j);
      max_prime = j;
    }
  }

  std::map<int, int> prime_factor(long long int x) {
    std::map<int, int> ret;
    if ((long long int)max_check * (long long int)max_check < x) {
      return ret;
    }
    for (int i = 0; i < prime_number; ++i) {
      if (x == 1) {
        break;
      }
      while (x % primes[i] == 0) {
        x /= primes[i];
        ret[primes[i]] += 1;
      }
    }
    if (x != 1) {
      ret[x] += 1;
    }
    return ret;
  }
};
