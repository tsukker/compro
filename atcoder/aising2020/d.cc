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

int naive(int x) {
  int ret = 0;
  while (0 < x) {
    x %= __builtin_popcount(x);
    ret += 1;
  }
  return ret;
}

void solve() {
  int m = 200005;
  vi preans(m, 0);
  ll debugsum = 0;
  rep (i, m) {
    preans.at(i) = naive(i);
    debugsum += preans[i];
  }
  //debug(debugsum);
  int n;
  scan(n);
  string x;
  scan(x);
  int pc = 0;
  rep (i, n) {
    if (x[i] == '1') {
      pc += 1;
    }
  }
  int pcp = pc + 1;
  int pcm = max(pc - 1, 1);
  debug2(pcp, pcm);
  vi pcp_r(m, 0);
  vi pcm_r(m, 0);
  pcp_r[0] = 1;
  pcm_r[0] = 1;
  rep (i, m - 1) {
    pcp_r.at(i + 1) = pcp_r.at(i) * 2 % pcp;
    pcm_r.at(i + 1) = pcm_r.at(i) * 2 % pcm;
  }
  int base_pcpr = 0;
  int base_pcmr = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (x[n-1 - i] == '1') {
      base_pcpr = (base_pcpr + pcp_r.at(i)) % pcp;
      base_pcmr = (base_pcmr + pcm_r.at(i)) % pcm;
    }
  }
  debug2(base_pcpr, base_pcmr);
  vi ans(n);
  for (int i = n - 1; i >= 0; --i) {
    if (x[n-1 - i] == '1') {
      if (pc == 1) {
        ans[n-1 - i] = 0;
        continue;
      }
      int current_pcmr = (base_pcmr + pcm - pcm_r.at(i)) % pcm;
      ans[n-1 - i] = 1 + preans.at(current_pcmr);
    } else {
      int current_pcpr = (base_pcpr + pcp_r.at(i)) % pcp;
      ans[n-1 - i] = 1 + preans.at(current_pcpr);
    }
  }
  rep (i, n) {
    print(ans.at(i));
  }
}

int main() {
  solve();
  return 0;
}
