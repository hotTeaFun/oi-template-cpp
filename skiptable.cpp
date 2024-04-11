#include <bits/stdc++.h>
using i64 = long long;
void solve() {
  int n;
  std::vector<int> arr(n);
  std::vector<i64> log2(n + 1);
  log2[0] = log2[1] = 0;
  log2[2] = 1;
  for (i64 i = 3; i <= n; i++) log2[i] = log2[i / 2] + 1;
  // st[i][j]=f(i,i+2^j-1)
  // query(i,j)=f(st[i][s],st[j - (1 << s) + 1][s]) s=log2[j - i + 1]
  std::vector<std::vector<i64>> st(n, std::vector<i64>(log2[n] + 2));
  for (i64 i = 0; i < n; i++) st[i][0] = arr[i];
  for (i64 j = 1; j <= log2[n] + 1; j++)
    for (i64 i = 0; i + (1 << j) - 1 < n; i++) {
      st[i][j] = st[i][j - 1] & st[i + (1 << (j - 1))][j - 1];
    }
  auto query = [&](i64 i, i64 j) {
    i64 s = log2[j - i + 1];
    return st[i][s] & st[j - (1 << s) + 1][s];
  };
}
int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}