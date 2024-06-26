#include <bits/stdc++.h>
using i64 = long long;
std::set<std::pair<int, int>> E;
struct SCC {
  int n;
  std::vector<std::vector<int>> adj;
  std::vector<int> stk;
  std::vector<int> dfn, low, bel;
  int cur, cnt;

  SCC() {}
  SCC(int n) { init(n); }

  void init(int n) {
    this->n = n;
    adj.assign(n, {});
    dfn.assign(n, -1);
    low.resize(n);
    bel.assign(n, -1);
    stk.clear();
    cur = cnt = 0;
  }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  void dfs(int x) {
    dfn[x] = low[x] = cur++;
    stk.push_back(x);

    for (auto y : adj[x]) {
      if (dfn[y] == -1) {
        dfs(y);
        low[x] = std::min(low[x], low[y]);
      } else if (bel[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }

    if (dfn[x] == low[x]) {
      int y;
      do {
        y = stk.back();
        bel[y] = cnt;
        stk.pop_back();
      } while (y != x);
      cnt++;
    }
  }

  std::vector<int> work() {
    for (int i = 0; i < n; i++) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
    return bel;
  }
};

struct EBCC {
  int n;
  std::vector<std::vector<int>> adj;
  std::vector<int> stk;
  std::vector<int> dfn, low, bel;
  int cur, cnt;

  EBCC() {}
  EBCC(int n) { init(n); }

  void init(int n) {
    this->n = n;
    adj.assign(n, {});
    dfn.assign(n, -1);
    low.resize(n);
    bel.assign(n, -1);
    stk.clear();
    cur = cnt = 0;
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int x, int p) {
    dfn[x] = low[x] = cur++;
    stk.push_back(x);

    for (auto y : adj[x]) {
      if (y == p) {
        continue;
      }
      if (dfn[y] == -1) {
        E.emplace(x, y);
        dfs(y, x);
        low[x] = std::min(low[x], low[y]);
      } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
        E.emplace(x, y);
        low[x] = std::min(low[x], dfn[y]);
      }
    }

    if (dfn[x] == low[x]) {
      int y;
      do {
        y = stk.back();
        bel[y] = cnt;
        stk.pop_back();
      } while (y != x);
      cnt++;
    }
  }

  std::vector<int> work() {
    dfs(0, -1);
    return bel;
  }

  struct Graph {
    int n;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> siz;
    std::vector<int> cnte;
  };
  Graph compress() {
    Graph g;
    g.n = cnt;
    g.siz.resize(cnt);
    g.cnte.resize(cnt);
    for (int i = 0; i < n; i++) {
      g.siz[bel[i]]++;
      for (auto j : adj[i]) {
        if (bel[i] < bel[j]) {
          g.edges.emplace_back(bel[i], bel[j]);
        } else if (i < j) {
          g.cnte[bel[i]]++;
        }
      }
    }
    return g;
  }
};

void solve() {}
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