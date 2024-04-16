#include <bits/stdc++.h>
constexpr int N = 510;
int matched[N];
std::vector<int> G[N];
bool vis[N];
int ans = 0;
bool hugarian(int id) {
  for (int j : G[id]) {
    if (vis[j]) {
      continue;
    }
    vis[j] = true;
    if (!matched[j] || hugarian(matched[j])) {
      matched[j] = id;
      return true;
    }
  }
  return false;
}
int n, m, e;
void solve() {
  std::cin >> n >> m >> e;
  int u, v;
  for (int i = 0; i < e; i++) {
    std::cin >> u >> v;
    G[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    memset(vis, 0, sizeof(vis));
    if (hugarian(i)) {
      ans++;
    }
  }
  std::cout << ans << "\n";
}
int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}