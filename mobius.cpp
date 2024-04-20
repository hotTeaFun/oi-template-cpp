#include <bits/stdc++.h>

using i64 = long long;

template <class T>
constexpr T power(T a, i64 b) {
  T res{1};
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
  i64 res = a * b - i64(1.L * a * b / p) * p;
  res %= p;
  if (res < 0) {
    res += p;
  }
  return res;
}

template <i64 P>
struct MInt {
  i64 x;
  constexpr MInt() : x{0} {}
  constexpr MInt(i64 x) : x{norm(x % getMod())} {}

  static i64 Mod;
  constexpr static i64 getMod() {
    if (P > 0) {
      return P;
    } else {
      return Mod;
    }
  }
  constexpr static void setMod(i64 Mod_) { Mod = Mod_; }
  constexpr i64 norm(i64 x) const {
    if (x < 0) {
      x += getMod();
    }
    if (x >= getMod()) {
      x -= getMod();
    }
    return x;
  }
  constexpr i64 val() const { return x; }
  constexpr MInt operator-() const {
    MInt res;
    res.x = norm(getMod() - x);
    return res;
  }
  constexpr MInt inv() const { return power(*this, getMod() - 2); }
  constexpr MInt &operator*=(MInt rhs) & {
    if (getMod() < (1ULL << 31)) {
      x = x * rhs.x % int(getMod());
    } else {
      x = mul(x, rhs.x, getMod());
    }
    return *this;
  }
  constexpr MInt &operator+=(MInt rhs) & {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MInt &operator-=(MInt rhs) & {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
  friend constexpr MInt operator*(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MInt operator+(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MInt operator-(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MInt operator/(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
    i64 v;
    is >> v;
    a = MInt(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
    return os << a.val();
  }
  friend constexpr bool operator==(MInt lhs, MInt rhs) {
    return lhs.val() == rhs.val();
  }
  friend constexpr bool operator!=(MInt lhs, MInt rhs) {
    return lhs.val() != rhs.val();
  }
};

template <>
i64 MInt<0>::Mod = 998244353;

constexpr int P = 1000000007;
using Z = MInt<0>;
std::unordered_map<int, Z> fMu;

constexpr int N = 1E7;
std::vector<int> minp, primes;
std::vector<Z> mu;

void sieve(int n) {
  minp.assign(n + 1, 0);
  mu.resize(n);
  primes.clear();

  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (minp[i] == 0) {
      mu[i] = -1;
      minp[i] = i;
      primes.push_back(i);
    }

    for (auto p : primes) {
      if (i * p > n) {
        break;
      }
      minp[i * p] = p;
      if (p == minp[i]) {
        break;
      }
      mu[i * p] = -mu[i];
    }
  }

  for (int i = 1; i <= n; i++) {
    mu[i] += mu[i - 1];
  }
}

Z sumMu(int n) {
  if (n <= N) {
    return mu[n];
  }
  if (fMu.count(n)) {
    return fMu[n];
  }
  if (n == 0) {
    return 0;
  }
  Z ans = 1;
  for (int l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans -= (r - l + 1) * sumMu(n / l);
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  sieve(N);

  int L, R;
  std::cin >> L >> R;
  L -= 1;

  Z ans = 0;
  for (int l = 1, r; l <= R; l = r + 1) {
    r = R / (R / l);
    if (l <= L) {
      r = std::min(r, L / (L / l));
    }

    ans += (power(Z(2), R / l - L / l) - 1) * (sumMu(r) - sumMu(l - 1));
  }

  std::cout << ans << "\n";

  return 0;
}
