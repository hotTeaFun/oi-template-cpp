#include <bits/stdc++.h>
using i64 = long long;
const int N = 2e5 + 1;
std::vector<int> pri;
bool not_prime[N];
int fac[N], cnt[N];
template <class T>
constexpr T qpow(T a, i64 b) {
  T res{1};
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}
void pre(int n = N) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
      fac[i] = i;
      cnt[i] = 1;
    }
    for (int pri_j : pri) {
      if (i * pri_j > n) break;
      not_prime[i * pri_j] = true;
      fac[i * pri_j] = pri_j;
      cnt[i * pri_j] = fac[i] == pri_j ? cnt[i] + 1 : 1;
      if (i % pri_j == 0) {
        break;
      }
    }
  }
}
void solve() {}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t = 1;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}