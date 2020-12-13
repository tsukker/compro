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

struct RXQ {
  using T = int; // type or class of monoid
  static T operate(const T& left, const T& right) {
    return left ^ right; // definition of operator
  }
  static constexpr T identity() { return T(0); } // 単位元
};

template<class Monoid>
class SegTree {
private:
  using T = typename Monoid::T;
  const int n;
  std::vector<T> t;

  void propagate_to(int i) { t[i] = Monoid::operate(t[2*i], t[2*i+1]); }

public:
  SegTree(int n_) : n(n_), t(2*n, Monoid::identity()) {}
  SegTree(const std::vector<T>& v) : n(v.size()), t(2*n) {
    copy(begin(v), end(v), begin(t) + n);
    for (int i = n-1; i > 0; --i) { propagate_to(i); }
  }
  template<class Itr>
  SegTree(Itr first, Itr last) : n(std::distance(first, last)), t(2*n) {
    copy(first, last, begin(t) + n);
    for (int i = n-1; i > 0; --i) { propagate_to(i); }
  }

  void set(int i, const T& x) {
    t[i += n] = x;
    while (i >>= 1) { propagate_to(i); }
  }

  T get(int i) { return t[i + n]; }

  T accumulate(int l, int r) {
    T accl = Monoid::identity(), accr = Monoid::identity();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) { accl = Monoid::operate(accl, t[l++]); }
      if (r & 1) { accr = Monoid::operate(t[r-1], accr); }
    }
    return Monoid::operate(accl, accr);
  }
};

void solve() {
  int n, q;
  scan(n, q);
  vi a(n);
  scan(a);
  auto segt = SegTree<RXQ>(a);
  rep (i, q) {
    int t, x, y;
    scan(t, x, y);
    x -= 1;
    if (t == 1) {
      int new_elm = segt.get(x) ^ y;
      segt.set(x, new_elm);
    } else {
      print(segt.accumulate(x, y));
    }
  }
}

int main() {
  solve();
  return 0;
}
