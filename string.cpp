#include <bits/stdc++.h>
using i64 = long long;
// 函数 z[i] 表示 s 和 s[i,n-1]（即以 s[i]
// 开头的后缀）的最长公共前缀（LCP）的长度 z[0]=0
std::vector<int> z_function(const std::string& s) {
  int n = (int)s.length();
  std::vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = std::max(0, r - i + 1);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

//  pi[i] 就是，子串 s[0...i] 最长的相等的真前缀与真后缀的长度。
// pi[0]=0
std::vector<int> prefix_function(const std::string& s) {
  int n = (int)s.length();
  std::vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

// span[i] 表示以s[i]为中心的最长奇数回文串长度为2*span[i]-1
std::vector<int> manachar(const std::string& s) {
  int n = s.size();
  std::vector<int> span(n);
  // manacher
  for (int i = 0, l = 0, r = -1; i < n; ++i) {
    span[i] = (i <= r ? std::min(span[l + r - i], r - i + 1) : 1);
    while (i - span[i] >= 0 && i + span[i] < n &&
           s[i - span[i]] == s[i + span[i]]) {
      ++span[i];
    }
    if (i + span[i] - 1 > r) {
      l = i - span[i] + 1;
      r = i + span[i] - 1;
    }
  }
  return span;
}
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