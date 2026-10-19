#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
string s;
long long ans;

struct SAM{
    int link[maxn << 1], ch[maxn << 1][30];
    int len[maxn << 1];
    int f[maxn << 1];
    int last, size;
    vector<int>v[maxn << 1];
    
    void init() {
        for (int i = 0; i <= 2 * maxn - 20; i++) v[i].clear();
        memset(len, 0, sizeof len);
        memset(ch, 0, sizeof ch);
        memset(link, 0, sizeof link);
        link[0] = -1;
        size = last = 0;
    }
    void extend(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            int p = last, cur = (++size);
            len[cur] = len[p] + 1;
            f[cur] = 1;
            while (p != -1 && !ch[p][c]) {
                ch[p][c] = cur;
                p = link[p];
            }
            if (p == -1) link[cur] = 0;
            else {
                int q = ch[p][c];
                if (len[q] == len[p] + 1) link[cur] = q;
                else {
                    int copy = (++size);
                    len[copy] = len[p] + 1;
                    link[copy] = link[q];
                    for (int i = 0; i < 26; i++) ch[copy][i] = ch[q][i];
                    while (p != -1 && ch[p][c] == q) {
                        ch[p][c] = copy;
                        p = link[p];
                    }
                    link[q] = link[cur] = copy;
                }
            }
            last = cur;
        }
        for (int i = 1; i <= size; i++) v[link[i]].push_back(i);
    }
    void dfs(int u) {
        for (int i = 0; i < v[u].size(); i++) {
            int y = v[u][i];
            dfs(y);
            f[u] += f[y];
        }
        if (f[u] > 1) ans = max(ans, 1ll * f[u] * len[u]);
    }
} sam;

signed main() {
    cin >> s;
    sam.init();
    sam.extend(s);
    sam.dfs(0);
    cout << ans;
    return 0;
}
