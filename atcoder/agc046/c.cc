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

struct ImosAction {
  int i, j, begin, end;
};

vi clean(string& s) {
  vi ret;
  int idx = 0;
  int n = s.size();
  rep (i, n) {
    if (s.at(i) == '0') {
      ret.push_back(i - idx);
      idx = i + 1;
    }
  }
  if (idx < n) {
    ret.push_back(n - idx);
  }
  return ret;
}

int mod = 998244353;
void solve() {
  string s;
  scan(s);
  int k;
  scan(k);
  k = min(k, 310);
  auto cleaned = clean(s);
  debug(s);
  debug(cleaned);
  vvll dp(k+1, vll(k+1, 0));
  dp[0][0] = 1;
  int sz = cleaned.size();
  rep (ic, sz) {
    vvll ndp = dp;
    vector<ImosAction> imos_actions;
    rep (i, k+1) {
      rep (j, k+1) {
        if (dp.at(i).at(j) == 0) {
          continue;
        }
        if (i + j > k) {
          break;
        }
        FOR (moved, 1, cleaned.at(ic) + 1) {
          if (i < moved) {
            break;
          }
          ndp.at(i - moved).at(j + moved) = (ndp.at(i - moved).at(j + moved) + dp.at(i).at(j)) % mod;
        }
        imos_actions.push_back(ImosAction{i, j, 1, k+1 - i - j});
        // FOR (total, i+j+1, k+1) {
        //   int should_moved = total - i - j;
        //   ndp.at(i + should_moved).at(j) = (ndp.at(i + should_moved).at(j) + dp.at(i).at(j)) % mod;
        // }
      }
    }
    vvll imos(k+2, vll(k+2, 0));
    for (auto action : imos_actions) {
      int i = action.i;
      int j = action.j;
      imos.at(i + action.begin).at(j) = (imos.at(i + action.begin).at(j) + dp.at(i).at(j)) % mod;
      imos.at(i + action.end).at(j) = (imos.at(i + action.end).at(j) + mod - dp.at(i).at(j)) % mod;
    }
    vvll accum_imos(k+1, vll(k+1, 0));
    rep (j, k+1) {
      rep (i, k) {
        accum_imos.at(i+1).at(j) = (accum_imos.at(i).at(j) + imos.at(i+1).at(j)) % mod;
        ndp.at(i+1).at(j) = (ndp.at(i+1).at(j) + accum_imos.at(i+1).at(j)) % mod;
      }
    }
    swap(dp, ndp);
    //debug2(ic, dp);
  }
  ll ans = 0;
  rep (i, k+1) {
    ans = (ans + dp.at(0).at(i)) % mod;
  }
  print(ans);
}

int main() {
  solve();
  return 0;
}
