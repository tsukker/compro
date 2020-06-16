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

void solve() {
  int n, q;
  scan(n, q);
  vi a(n);
  scan(a);
  vi s(q);
  scan(s);
  vi acc(n+1, 0);
  rep (i, n) {
    acc.at(i+1) = gcd(acc.at(i), a.at(i));
  }
  rep (i, q) {
    int g = gcd(s.at(i), acc.at(n));
    if (g > 1) {
      print(g);
      continue;
    }
    int ng = 0;
    int ok = n;
    while (ok - ng > 1) {
      int mid = (ng + ok) / 2;
      if (gcd(s.at(i), acc.at(mid)) == 1) {
        ok = mid;
      } else {
        ng = mid;
      }
    }
    print(ok);
  }
}

int main() {
  solve();
  return 0;
}
