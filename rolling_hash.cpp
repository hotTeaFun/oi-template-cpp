#include <bits/stdc++.h>
using i64 = long long;
template <i64 mod = i64(1e9 + 7), i64 p = 233>
struct StrHasher {
  std::vector<i64> P;
  std::vector<i64> h;

 private:
  i64 do_query(int l, int r, const std::vector<i64>& hv,
               const std::vector<i64>& Pv) {
    return (hv[r + 1] - ((Pv[r - l + 1] * hv[l]) % mod) + mod) % mod;
  }

 public:
  StrHasher(std::string& s = "") {
    if (s != "") {
      hash_str(s);
    }
  }
  void hash_str(const std::string& s) {
    int n = s.size();
    P = std::vector<i64>(n + 1);
    P[0] = 1;
    for (int i = 1; i <= n; i++) {
      P[i] = (P[i - 1] * p) % mod;
    }
    h = std::vector<i64>(n + 1);
    h[0] = h[2] = 0;
    for (int i = 0; i < n; i++) {
      h[i + 1] =
          (h[i] * p + (isdigit(s[i]) ? s[i] - '0' + 27 : s[i] - 'a' + 1)) % mod;
    }
  }
  i64 query(int l, int r) { return {do_query(l, r, h, P)}; }
};

void solve() {}
int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}