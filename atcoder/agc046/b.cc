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

struct Count {
  ll total, top_1, right_1;
};

ll a, b, c, d;

void check(vector<vector<Count>>& dp) {
  vvll dp_(c+1, vll(d+1, 0));
  FOR (i, a, c+1) {
    FOR (j, b, d+1) {
      dp_.at(i).at(j) = dp.at(i).at(j).total;
    }
  }
  debug(dp_);
}

ll mod = 998244353;
void solve() {

  scan(a, b, c, d);
  vector<vector<Count>> dp(c+1, vector<Count>(d+1, Count{0, 0, 0}));
  dp.at(a).at(b) = Count{1, 0, 0};
  FOR (i, a+1, c+1) {
    auto cnt = dp.at(i-1).at(b);
    ll total = cnt.total * b % mod;
    ll top_1 = total;
    ll right_1 = (cnt.right_1 * (b - 1) + (cnt.total - cnt.right_1)) % mod;
    dp.at(i).at(b) = Count{total, top_1, right_1};
  }
  FOR (j, b+1, d+1) {
    auto cnt = dp.at(a).at(j-1);
    ll total = cnt.total * a % mod;
    ll right_1 = total;
    ll top_1 = (cnt.top_1 * (a - 1) + (cnt.total - cnt.top_1)) % mod;
    dp.at(a).at(j) = Count{total, top_1, right_1};
  }
  FOR (i, a+1, c+1) {
    FOR (j, b+1, d+1) {
      // dp[i][j]
      auto left = dp.at(i).at(j-1);
      auto bottom = dp.at(i-1).at(j);
      ll top_1 = (left.top_1 * (i - 1) + bottom.right_1 * 1 + (bottom.total - bottom.right_1) * j) % mod;
      ll right_1 = (bottom.right_1 * (j - 1) + left.top_1 * 1 + (left.total - left.top_1) * i) % mod;
      ll total = (left.total * i + bottom.total * j + mod - left.top_1 * (i - 1) % mod) % mod;
      assert ((left.top_1 * (i - 1) - bottom.right_1 * (j - 1)) % mod == 0);
      dp.at(i).at(j) = Count{total, top_1, right_1};
    }
  }
  //check(dp);
  print(dp.at(c).at(d).total);

}

int main() {
  solve();
  return 0;
}
