#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
int n;
char s[maxn];
int w, sa[maxn << 1], rk[maxn << 1], oldrk[maxn << 1], h[maxn];

signed main() {
    cin >> n;
    cin >> (s + 1);
    for(int i = 1; i <= n; i++) sa[i] = i, rk[i] = s[i];
    for(w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1, [](int x, int y){
            return (rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y]);
        });
        memcpy(oldrk, rk, sizeof(rk));
        for(int cnt = 0, i = 1; i <= n; i++) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = cnt;
            else
                rk[sa[i]] = (++cnt);
        }
    }
    for(int k = 0, i = 1; i <= n; i++) {
        if (rk[i] == 0) continue;
        if(k) k--;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
        h[rk[i]] = k;
    }
    return 0;
}
