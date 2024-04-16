#include <bits/stdc++.h>

struct SuffixArray {
  // 后缀i:s[i...n]
  // sa[i] 表示将所有后缀排序后第 i 小的后缀的编号
  // rk[i] 表示后缀 i 的排名
  // height[i]=lcp(sa[i],sa[i-1])，即第 i 名的后缀与它前一名的后缀的最长公共前缀
  // height[1]=0
  std::vector<int> sa, rk, height;
  // s[1...n]为实际字符串,s[0]留空
  SuffixArray(const std::string& s) {
    int n = s.size() - 1;
    sa = std::vector<int>(n + 1);
    rk = std::vector<int>(2 * n + 1);
    std::vector<int> oldrk(2 * n + 1);
    for (int i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
    for (int w = 1; w < n; w <<= 1) {
      std::sort(next(begin(sa)), end(sa), [&](int x, int y) {
        return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
      });
      std::copy(begin(rk), end(rk), begin(oldrk));
      for (int p = 0, i = 1; i <= n; ++i) {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
            oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
          rk[sa[i]] = p;
        } else {
          rk[sa[i]] = ++p;
        }
      }
    }
    height = std::vector<int>(n + 1);
    for (int i = 1, k = 0; i <= n; ++i) {
      if (rk[i] == 0) continue;
      if (k) --k;
      while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
      height[rk[i]] = k;
    }
  }
};
int main() {
  std::string s;
  std::cin >> s;
  s.insert(begin(s), '0');
  int n = s.size() - 1;
  SuffixArray sa(s);
  int res = n * (n + 1) / 2 -
            std::accumulate(next(begin(sa.height), 2), end(sa.height), 0);
  std::cout << res << "\n";
  return 0;
}
