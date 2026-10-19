#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e7 + 10;
string a, b;
int z[maxn], e[maxn];
int ansz, ansp;

signed main() {
    cin >> a >> b;
    z[0] = b.size();
    for(int r = 1, c = 1, i = 1; i < b.size(); i++) {
        int len = (i < r ? min(r - i, z[i - c]) : 0ll);
        while (i + len < b.size() && b[i + len] == b[len]) len++;
        if (i + len > r) { r = i + len; c = i; }
        z[i] = len;
    }
    for(int r = 0, c = 0, i = 0; i < a.size(); i++) {
        int len = (i < r ? min(r - i, z[i - c]) : 0ll);
        while (i + len < a.size() && len < b.size() && a[i + len] == b[len]) len++;
        if (i + len > r) { r = i + len; c = i; }
        e[i] = len;
    }
    for(int i = 0; i < b.size(); i++) ansz ^= ((i + 1ll) * (z[i] + 1ll));
    for(int i = 0; i < a.size(); i++) ansp ^= ((i + 1ll) * (e[i] + 1ll));
    cout << ansz << '\n';
    cout << ansp << '\n';
    return 0;
}
