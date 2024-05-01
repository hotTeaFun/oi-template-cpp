#include <bits/stdc++.h>

using i64 = long long;
struct PAM {
    static constexpr int ALPHABET_SIZE = 28;
    struct Node {
        int len;
        int link;
        int cnt;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    std::vector<Node> t;
    int suff;
    std::string s;
    PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    bool add(char c, char offset = 'a') {
        int pos = s.size();
        s += c;
        int let = c - offset;
        int cur = suff, curlen = 0;

        while (true) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;  
            cur = t[cur].link;
        }       
        if (t[cur].next[let]) {  
            suff = t[cur].next[let];
            return false;
        }
        
        int num = newNode();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;

        if (t[num].len == 1) {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }

        while (true) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[num].link = t[cur].next[let];
                break;
            }       
        }           

        t[num].cnt = 1 + t[t[num].link].cnt;

        return true;
    }
};

PAM pam;
i64 get(std::string s) {
    pam.init();
    int n = s.size();
    // std::cerr << s << "\n";
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pam.add(s[i]);
        pos[i] = pam.suff;
    }
    int N = pam.t.size();
    std::vector<int> l(N, n), r(N, -1);
    for (int i = 0; i < n; i++) {
        l[pos[i]] = std::min(l[pos[i]], i);
        r[pos[i]] = std::max(r[pos[i]], i);
    }
    for (int i = N - 1; i >= 2; i--) {
        l[pam.t[i].link] = std::min(l[pam.t[i].link], l[i]);
        r[pam.t[i].link] = std::max(r[pam.t[i].link], r[i]);
    }
    std::vector<int> d(n);
    for (int i = 2; i < N; i++) {
        if (l[i] + pam.t[i].len <= r[i]) {
            d[l[i]]++;
            d[r[i] - pam.t[i].len + 1]--;
        }
    }
    for (int i = 1; i < n; i++) {
        d[i] += d[i - 1];
    }
    i64 ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += 1LL * d[i] * d[i];
    }
    // std::cerr << ans << "\n";
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    auto check = [&](i64 x) {
        int res = 0;
        for (int i = 0; i < n; ) {
            int len = 1;
            while (i + len <= n && get(s.substr(i, len)) <= x) {
                len *= 2;
            }
            int j = 0;
            while (len > 1) {
                len /= 2;
                if (i + j + len <= n && get(s.substr(i, j + len)) <= x) {
                    j += len;
                }
            }
            i += j;
            res++;
        }
        return res <= k;
    };
    
    i64 lo = 0, hi = 1E18;
    while (lo < hi) {
        i64 x = (lo + hi) / 2;
        if (check(x)) {
            hi = x;
        } else {
            lo = x + 1;
        }
    }
    std::cout << lo << "\n";
    
    return 0;
}