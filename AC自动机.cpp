#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
string S, T;
int n, ans[maxn];

struct ACAM {
    int trie[maxn][26], fail[maxn], fail_in[maxn], var[maxn], point;
    vector<int> end[maxn];

    void build_s(string s, int id) {
        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (!trie[p][c]) trie[p][c] = ++point;
            p = trie[p][c];
        }
        end[p].push_back(id);
    }

    void build_fail() {
        queue<int> p;
        for (int i = 0; i < 26; i++) 
            if (trie[0][i]) p.push(trie[0][i]);
        while (!p.empty()) {
            int u = p.front(); p.pop();
            for (int i = 0; i < 26; i++) {
                if (trie[u][i]) {
                    fail[trie[u][i]] = trie[fail[u]][i];
                    fail_in[fail[trie[u][i]]]++;
                    p.push(trie[u][i]);
                } else trie[u][i] = trie[fail[u]][i];
            }
        }
    }

    void query(string s) {
        int len = s.size(), p = 0;
        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            p = trie[p][c];
            var[p]++;
        }
    }

    void get_var() {
        queue<int> p;
        for (int i = 0; i <= point; i++) 
            if (!fail_in[i]) p.push(i);
        while (!p.empty()) {
            int u = p.front(); p.pop();
            var[fail[u]] += var[u];
            fail_in[fail[u]]--;
            if (!fail_in[fail[u]]) p.push(fail[u]);
        }
        for (int i = 0; i <= point; i++) 
            if (end[i].size()) 
                for (int j = 0; j < end[i].size(); j++) 
                    ans[end[i][j]] = var[i];
    }
} AC;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> S, AC.build_s(S, i);
    cin >> T;
    AC.build_fail();
    AC.query(T);
    AC.get_var();
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}
