#include <bits/stdc++.h>
using i64 = long long;
#define li (i << 1)
#define ri (i << 1 | 1)
#define mid (l + r >> 1)

struct d {
  // 1(white); 0(black)
  int w, b, pw, pb;
  d(int w = 0, int b = 0, int pw = 0, int pb = 0)
      : w(w), b(b), pw(pw), pb(pb) {}
};
inline d hb(d i, d j) {
  int pw, pb;
  if (i.pw) {
    pw = i.pw;
  } else {
    pw = j.pw;
  }
  if (i.pb) {
    pb = i.pb;
  } else {
    pb = j.pb;
  }
  return d(i.w + j.w, i.b + j.b, pw, pb);
}
struct SegTree {
  std::vector<d> dat;
  std::vector<int> len, tg2;
  SegTree(const std::string& s) {
    int n = s.size();
    dat = std::vector<d>(n << 2);
    len = std::vector<int>(n << 2);
    tg2 = std::vector<int>(n << 2);
    build(1, 1, n, s);
  }
  inline void P(int i) {
    d& t = dat[i];
    tg2[i] ^= 1, std::swap(t.w, t.b), std::swap(t.pw, t.pb);
  }
  inline void pd(int i) {
    if (tg2[i]) P(li), P(ri);
    tg2[i] = 0;
  }
  void build(int i, int l, int r, const std::string& s) {
    len[i] = r - l + 1;
    if (l == r) {
      int t = s[l - 1] - '0';
      dat[i] = d(t, t ^ 1, t ? l : 0, t ? 0 : l);
      return;
    }
    build(li, l, mid, s);
    build(ri, mid + 1, r, s);
    dat[i] = hb(dat[li], dat[ri]);
  }
  void Mdf(int i, int l, int r, int a, int b) {
    if (b < l || r < a) return;
    if (a <= l && r <= b) {
      P(i);
      return;
    }
    pd(i);
    Mdf(li, l, mid, a, b), Mdf(ri, mid + 1, r, a, b);
    dat[i] = hb(dat[li], dat[ri]);
  }
  d Qur(int i, int l, int r, int a, int b) {
    if (b < l || r < a) return d();
    if (a <= l && r <= b) return dat[i];
    pd(i);
    return hb(Qur(li, l, mid, a, b), Qur(ri, mid + 1, r, a, b));
  }
};
void solve() {
  int n;
  std::cin >> n;
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