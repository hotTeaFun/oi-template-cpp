#include <bits/stdc++.h>
constexpr int N = 1e4 + 10;

int dfn[N];  // dfn记录访问时间戳
int low[N];  // low记录从每个节点能到达节点中的最小时间戳

int tot;              // tot维护当前时间
std::stack<int> stk;  // 访问栈
bool instk[N];        // 记录节点是否在栈上
int nscc;             // 记录总共有多少个scc
int scc[N];           // 记录每个节点属于哪个scc
int sscc[N];          // 记录每个scc的大小
int n, m;
std::vector<int> G[N];
void tarjan(int id) {
  dfn[id] = low[id] = ++tot;
  stk.push(id);
  instk[id] = true;
  for (int j : G[id]) {
    if (!dfn[j]) {
      tarjan(j);
      low[id] = std::min(low[id], low[j]);
    } else if (instk[j]) {
      low[id] = std::min(low[id], dfn[j]);
    }
  }
  if (dfn[id] == low[id]) {
    int j;
    ++nscc;
    do {
      j = stk.top();
      stk.pop();
      instk[j] = false;
      scc[j] = nscc;
      sscc[nscc]++;
    } while (j != id);
  }
}
void solve() {
  std::cin >> n >> m;
  int u, v;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    G[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  int cnt = 0;
  for (int i = 1; i <= nscc; i++) {
    if (sscc[i] > 1) {
      cnt++;
    }
  }
  std::cout << cnt << "\n";
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