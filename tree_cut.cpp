#include <bits/stdc++.h>
using i64 = long long;
#define lc o << 1
#define rc o << 1 | 1
struct SegTree {
  std::vector<i64> sum;
  int n;
  SegTree(int n = 0) : n(n), sum(std::vector<i64>(n << 2, 0)) {}
  void build(int o, int l, int r, const std::vector<i64>& w,
             const std::vector<int>& rnk) {
    if (l == r) {
      sum[o] = w[rnk[l]];
      return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid, w, rnk);
    build(rc, mid + 1, r, w, rnk);
    sum[o] = sum[lc] + sum[rc];
  }
  int query(int o, int l, int r, int ql, int qr) {  // query sum
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return sum[o];
    int mid = (l + r) >> 1;
    return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
  }

  void update(int o, int l, int r, int x, int t) {  // a[x] = t
    if (l == r) {
      sum[o] = t;
      return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc, l, mid, x, t);
    else
      update(rc, mid + 1, r, x, t);
    sum[o] = sum[lc] + sum[rc];
  }
};

struct TreeCut {
  int n, cnt, cur;
  std::vector<int> h, p, son, siz, dep, dfn, fa, top, rnk, nxt;
  TreeCut(int n)
      : n(n),
        cnt(0),
        cur(0),
        h(std::vector<int>(n + 1)),
        p(std::vector<int>(2 * n)),
        son(std::vector<int>(n + 1)),
        siz(std::vector<int>(n + 1)),
        dep(std::vector<int>(n + 1)),
        dfn(std::vector<int>(n + 1)),
        fa(std::vector<int>(n + 1)),
        top(std::vector<int>(n + 1)),
        rnk(std::vector<int>(n + 1)),
        nxt(std::vector<int>(2 * n)) {}
  SegTree st;
  void init(const std::vector<std::pair<int, int>>& edges,
            const std::vector<i64>& w) {
    for (auto [x, y] : edges) {
      add_edge(x, y);
      add_edge(y, x);
    }
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    st = SegTree(n);
    st.build(1, 1, n, w, rnk);
  }

 private:
  void add_edge(int x, int y) {
    cur++;
    nxt[cur] = h[x];
    h[x] = cur;
    p[cur] = y;
  }
  void dfs1(int o) {
    son[o] = -1;
    siz[o] = 1;
    for (int j = h[o]; j; j = nxt[j])
      if (!dep[p[j]]) {
        dep[p[j]] = dep[o] + 1;
        fa[p[j]] = o;
        dfs1(p[j]);
        siz[o] += siz[p[j]];
        if (son[o] == -1 || siz[p[j]] > siz[son[o]]) son[o] = p[j];
      }
  }

  void dfs2(int o, int t) {
    top[o] = t;
    cnt++;
    dfn[o] = cnt;
    rnk[cnt] = o;
    if (son[o] == -1) return;
    dfs2(son[o], t);
    for (int j = h[o]; j; j = nxt[j])
      if (p[j] != son[o] && p[j] != fa[o]) dfs2(p[j], p[j]);
  }

 public:
  int querysum(int x, int y) {
    int ret = 0, fx = top[x], fy = top[y];
    while (fx != fy) {
      if (dep[fx] >= dep[fy])
        ret += st.query(1, 1, n, dfn[fx], dfn[x]), x = fa[fx];
      else
        ret += st.query(1, 1, n, dfn[fy], dfn[y]), y = fa[fy];
      fx = top[x];
      fy = top[y];
    }
    if (dfn[x] < dfn[y])
      ret += st.query(1, 1, n, dfn[x], dfn[y]);
    else
      ret += st.query(1, 1, n, dfn[y], dfn[x]);
    return ret;
  }
};
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