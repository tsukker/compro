#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define FOR(i,k,n) for(int(i)=(k);(i)<(n);++(i))
#define rep(i,n) FOR(i,0,n)
#define all(v) begin(v),end(v)
#ifdef ONLINE_JUDGE
  #define debug(x)
  #define debug2(x,y)
  #define debug3(x,y,z)
  #define assert(e) if(!(e)){stod("");}
#else
  #define debug(x) std::cerr<<#x<<": "<<x<<"\n"
  #define debug2(x,y) std::cerr<<#x<<": "<<x<<", "<<#y<<": "<<y<<"\n"
  #define debug3(x,y,z) std::cerr<<#x<<": "<<x<<", "<<#y<<": "<<y<<", "<<#z<<": "<<z<<"\n"
#endif

using ll=long long;
using vi=std::vector<int>;
using vvi=std::vector<vi>;
using vll=std::vector<ll>;
using vvll=std::vector<vll>;
template<typename T> using vvec=std::vector<std::vector<T>>;
template<typename T>
auto make_v(size_t sz){return std::vector<T>(sz);}
template<typename T,typename... Ts>
auto make_v(size_t sz,Ts...ts){return std::vector<decltype(make_v<T>(ts...))>(sz,make_v<T>(ts...));}
template<typename T>
void fill_v(T&var,const T&x){var=x;}
template<typename V,typename T>
void fill_v(V&v,const T&x){for(auto&& w:v){fill_v(w,x);}}

template<typename T> std::ostream& operator<<(std::ostream&s,const std::vector<T>&v){
  int sz=v.size();s<<"\n";rep(i,sz){s<<v[i];if(i<sz-1){s<<"\t";}}s<<"\n";return s;}
template<typename T> std::ostream& operator<<(std::ostream&s,const std::vector<std::vector<T>>&v){
  for(auto&& w:v){s<<w;}return s;}
template<typename T> std::ostream& operator<<(std::ostream&s,const std::deque<T>&v){
  int sz=v.size();s<<"\n";rep(i,sz){s<<v[i];if(i<sz-1){s<<"\t";}}s<<"\n";return s;}
template<typename T> std::ostream& operator<<(std::ostream&s,const std::deque<std::deque<T>>&v){
  for(auto&& w:v){s<<w;}return s;}
template<typename T> std::ostream& operator<<(std::ostream&s, const std::set<T>&v){
  s<<"\n";for(auto&& elm:v){s<<elm<<"\t";}s<<"\n";return s;}

inline void scan(int&a){scanf("%d",&a);}
inline void scan(ll&a){scanf("%lld",&a);}
inline void scan(char&a){scanf(" %c",&a);}
inline void scan(double&a){scanf("%lf",&a);}
template<typename T>
inline void scan(std::vector<T>&v){for(auto&& sv:v){scan(sv);}}
template<typename First,typename...Args>
inline void scan(First&f,Args&...args){scan(f);scan(args...);}
inline void scan(std::string&s){char BUF[3000000];scanf(" %s",BUF);s=std::string(BUF);}
inline void print(int a){printf("%d\n",a);}
inline void print(ll a){printf("%lld\n",a);}
inline void print(double a){printf("%.12f\n",a);}
inline void print(std::string s){std::cout<<s<<"\n";}

using namespace std;

const int mod = 1000000007;
ll po(ll k, ll x) {
  if (x == 0) {
    return 1;
  }
  if (x == 1) {
    return k % mod;
  }
  ll y = po(k, x/2);
  y = y * y % mod;
  if (x % 2 == 1) {
    y = y * k % mod;
  }
  return y;
}

ll combination(ll n, ll k, vll& frac, vll& finv) {
  k = min(k, n-k);
  if (k == 0) {
    return 1;
  }
  ll ret = frac.at(n);
  ll denomi = finv.at(k) * finv.at(n-k) % mod;
  ret = ret * denomi % mod;
  return ret;
}

ll naive(int n, int m, vll& frac, vll& finv) {
  vll a(n);
  rep (i, n) {
    a.at(i) = i;
  }
  debug(a);
  vll b(n);
  ll ans = 0;
  int k_max = m - n + 1;
  rep (i, min(n + 1, k_max)) {
    rep (j, n - i) {
      b.at(j) = a.at(j);
    }
    rep (j, i) {
      b.at(n - i + j) = n + j;
    }
    debug(b);
    ll cans = 0;
    do {
      bool ok = true;
      rep (j, n) {
        if (a.at(j) == b.at(j)) {
          ok = false;
        }
      }
      if (ok) {
        cans += 1;
      }
    } while (next_permutation(all(b)));
    cans = cans * combination(n, n - i, frac, finv) % mod * combination(m-n, i, frac, finv) % mod;
    ans = (ans + cans) % mod;
    debug2(i, ans);
  }
  debug(ans);
  debug2(combination(m, n, frac, finv), frac.at(n));
  //ans = ans * combination(m, n, frac, finv) % mod * frac.at(n) % mod;
  //debug(ans);

  return ans;
}

void solve() {
  ll n, m;
  scan(n, m);
  ll nm_max = 5 * 100005;
  vll frac(nm_max, 0);
  frac.at(0) = 1;
  rep (i, nm_max - 1) {
    frac.at(i + 1) = frac.at(i) * (i + 1) % mod;
  }
  vll finv(nm_max, 0);
  finv.at(nm_max - 1) = po(frac.at(nm_max - 1), mod-2);
  for (int i = nm_max - 2; i >= 0; --i) {
    finv.at(i) = finv.at(i + 1) * (i + 1) % mod;
  }

  // ll ans = naive(n, m, frac, finv);
  // print(ans);
  // return;

  // a: any possible
  ll a = combination(m, n, frac, finv) * frac.at(n) % mod;

  vll fm(n+1, 0);
  fm[0] = 1;
  fm[1] = m - n;
  FOR (i, 2, n+1) {
    // cf.) https://ja.wikipedia.org/wiki/完全順列
    // n = i, m = i + m - n
    fm[i] = (fm[i-1] * (i + m - n - 1) + fm[i-2] * (i - 1)) % mod;
  }
  ll ans = a * fm[n] % mod;
  print(ans);
}

void solve_editorial() {
  ll n, m;
  scan(n, m);
  ll nm_max = 5 * 100005;
  vll frac(nm_max, 0);
  frac.at(0) = 1;
  rep (i, nm_max - 1) {
    frac.at(i + 1) = frac.at(i) * (i + 1) % mod;
  }
  vll finv(nm_max, 0);
  finv.at(nm_max - 1) = po(frac.at(nm_max - 1), mod-2);
  for (int i = nm_max - 2; i >= 0; --i) {
    finv.at(i) = finv.at(i + 1) * (i + 1) % mod;
  }
  ll ans = 0;
  rep (i, n+1) {
    ll matching_part = combination(n, i, frac, finv) * frac.at(m) % mod * finv.at(m - i) % mod;
    ll permutation_m_i = frac.at(m - i) * finv.at(m - n) % mod;
    ll pans = matching_part * permutation_m_i % mod * permutation_m_i % mod;
    if (i % 2 == 0) {
      ans = (ans + pans) % mod;
    } else {
      ans = (ans + mod - pans) % mod;
    }
  }
  print(ans);
}

int main() {
  // solve();
  solve_editorial();
  return 0;
}
