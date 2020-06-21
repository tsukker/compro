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

/*
k = 1, s = "aa"
aaa ... aaz 26
aba ... aza 25
baa ... zaa 25
-> 76
k = 1, s = "ab"
aba ... abz 26
aab, acb ... azb 25
bab ... zab
-> 76
*/

ll mod = 1000000007;

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

ll combination(ll n, ll k, const vll& frac, const vll& frev) {
  k = min(k, n-k);
  if (k == 0) {
    return 1;
  }
  ll ret = frac.at(n);
  ll denomi = frev.at(k) * frev.at(n-k) % mod;
  ret = ret * denomi % mod;
  return ret;
}

ll mod_mult(vll& a) {
  ll ret = 1;
  for (ll x : a) {
    ret = ret * x % mod;
  }
  return ret;
}

ll calc(ll k, string& s) {
  ll m = s.length();
  ll n = k + m;
  ll ans = 0;
  vll po25(n+1), po26(n+1), frac(n+1);
  po25.at(0) = 1;
  po26.at(0) = 1;
  frac.at(0) = 1;
  rep (i, n) {
    po25.at(i + 1) = po25.at(i) * 25 % mod;
    po26.at(i + 1) = po26.at(i) * 26 % mod;
    frac.at(i + 1) = frac.at(i) * (i + 1) % mod;
  }
  vll frev(n+1);
  frev.at(n) = po(frac.at(n), mod-2);
  for (int i = n-1; i >= 0; --i) {
    frev.at(i) = frev.at(i + 1) * (i + 1) % mod;
  }
  FOR (i, m-1, n) {
    vll a = {combination(i, m-1, frac, frev), po25.at(i - (m-1)), po26.at(n-1 - i)};
    ans = (ans + mod_mult(a)) % mod;
  }
  return ans;
}

void solve() {
  ll k;
  scan(k);
  string s;
  scan(s);
  ll ans = calc(k, s);
  print(ans);
}

int main() {
  solve();
  return 0;
}
