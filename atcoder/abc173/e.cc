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

int mod = 1000000007;
void print_(ll ans) {
  ans %= mod;
  if (ans < 0) {
    ans += mod;
  }
  print(ans);
  exit(0);
}

ll calc_answer();
void pos_empty_zer_empty(vll& neg, int k) {
  if (k % 2 == 0) {
    sort(all(neg));
  } else {
    sort(all(neg), greater<ll>());
  }
  ll ans = 1;
  rep (i, k) {
    ans = ans * neg.at(i) % mod;
  }
  if (ans < 0) {
    ans += mod;
  }
  print_(ans);
}

void no_need_to_use_zero_pos_empty(vll& neg, int k) {
  if (k % 2 == 0) {
    sort(all(neg));
  } else {
    sort(all(neg), greater<ll>());
  }
  ll ans = 1;
  rep (i, k) {
    ans = ans * neg.at(i) % mod;
  }
  print_(ans);
}

void no_need_to_use_zero(vll& pos, vll& neg, int k) {
  ll ans = 1;
  sort(all(pos), greater<ll>());
  if (k % 2 == 1) {
    ans = pos[0];
    pos.erase(begin(pos));
    k -= 1;
  }
  vll pos_elms;
  rep (i, (int)pos.size() / 2) {
    ll elm = pos.at(i * 2) * pos.at(i * 2 + 1);
    pos_elms.push_back(elm);
  }
  sort(all(neg));
  vll neg_elms;
  rep (i, (int)neg.size() / 2) {
    ll elm = neg.at(i * 2) * neg.at(i * 2 + 1);
    neg_elms.push_back(elm);
  }
  debug(pos_elms);
  debug(neg_elms);
  size_t pos_idx = 0;
  size_t neg_idx = 0;
  while (k > 0) {
    k -= 2;
    if (pos_idx == pos_elms.size()) {
      ans = neg_elms.at(neg_idx) % mod * ans % mod;
      neg_idx += 1;
    } else if (neg_idx == neg_elms.size()) {
      ans = pos_elms.at(pos_idx) % mod * ans % mod;
      pos_idx += 1;
    } else if (pos_elms.at(pos_idx) < neg_elms.at(neg_idx)) {
      ans = neg_elms.at(neg_idx) % mod * ans % mod;
      neg_idx += 1;
    } else {
      ans = pos_elms.at(pos_idx) % mod * ans % mod;
      pos_idx += 1;
    }
  }
  print_(ans);
}

void solve() {
  int n, k;
  scan(n, k);
  vll a(n);
  scan(a);
  vll pos, neg, zer;
  rep (i, n) {
    if (a.at(i) < 0) {
      neg.push_back(a.at(i));
    } else if (a.at(i) == 0) {
      zer.push_back(a.at(i));
    } else {
      pos.push_back(a.at(i));
    }
  }
  if (pos.empty()) {
    if (zer.empty()) {
      pos_empty_zer_empty(neg, k);
    }
    if (k % 2 == 1 || (int)neg.size() < k) {
      print_(0);
    }
    pos_empty_zer_empty(neg, k);
  }
  if ((int)pos.size() + neg.size() < k) {
    // need to use 0
    print_(0);
  } else if ((int)pos.size() + neg.size() == k && (int)neg.size() % 2 == 1) {
    // use 0 if possible
    if (zer.empty()) {
      ll ans = 1;
      for (ll posnum : pos) {
        ans = ans * posnum % mod;
      }
      for (ll negnum : neg) {
        ans = ans * negnum % mod;
      }
      print_(ans);
    } else {
      print_(0);
    }
  } else {
    // no need to use 0
    // can use even number of negative elements
    if (pos.empty()) {
      no_need_to_use_zero_pos_empty(neg, k);
    } else {
      no_need_to_use_zero(pos, neg, k);
    }
  }
}

int main() {
  solve();
  return 0;
}
