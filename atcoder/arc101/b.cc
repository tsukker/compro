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

ll inversion_number(vi& a) {
  int n = a.size();
  if (n == 1) {
    return 0LL;
  }
  vi b;
  b.insert(b.begin(), a.begin(), a.begin() + (n/2));
  vi c;
  c.insert(c.begin(), a.begin() + (n/2), a.end());
  ll b_ret = inversion_number(b);
  ll c_ret = inversion_number(c);
  ll ans = b_ret + c_ret;
  int a_idx = 0;
  int b_idx = 0;
  int c_idx = 0;
  while (a_idx < n) {
    if (b_idx == n/2) {
      a.at(a_idx) = c.at(c_idx);
      c_idx += 1;
    } else if (c_idx == n - n/2) {
      a.at(a_idx) = b.at(b_idx);
      b_idx += 1;
    } else if (b.at(b_idx) <= c.at(c_idx)) {
      a.at(a_idx) = b.at(b_idx);
      b_idx += 1;
    } else {
      a.at(a_idx) = c.at(c_idx);
      ans += (n/2 - b_idx);
      c_idx += 1;
    }
    a_idx += 1;
  }
  return ans;
}

/*
If piv is the answer then there are floor(m / 2) + 1 or more subsequences which median is <= piv,
and floor(m / 2) + 1 -th median is exactly equal to piv
where m = Combination(n + 1, 2) = (n + 1) * n / 2.
("<=" means "less than or equal to")
This function returns true if and only if
there are >= floor(m / 2) + 1 subsequences which median is <= piv;
i.e. the subsequences contain >= floor(l / 2) + 1 elements which is <= piv
where l is the size of that subsequence.
This is equivalent to that the number of elements which is <= piv
is _strictly_ larger than the number of elements which is > piv.

This function takes O(N logN) time, so overall time complexity is O(N logN logM) where M is the range of a[i].
*/
bool is_ok(vi& a, int piv) {
  ll n = a.size();
  ll m = (n + 1) * n / 2;
  vi b(n, -1);
  rep (i, n) {
    if (a.at(i) > piv) {
      b.at(i) = 1;
    }
  }
  vi accum(n+1, 0);
  rep(i, n) {
    accum.at(i + 1) = accum.at(i) + b.at(i);
  }
  debug(accum);
  ll inv_num = inversion_number(accum);
  debug3(piv, m, inv_num);
  debug3(a, b, accum);
  return (inv_num >= m / 2 + 1);
}

void solve() {
  int n;
  scan(n);
  vi a(n);
  scan(a);
  int ng = 0;
  int ok = 1000456789;
  while (ok - ng > 1) {
    int mid = (ok + ng) / 2;
    if (is_ok(a, mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  print(ok);
}

int main() {
  solve();
  return 0;
}
