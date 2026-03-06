#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 2000005;

int a[MAXN], b[MAXN];
int cntA[MAXN], cntB[MAXN];
int head[MAXN], nxt[MAXM], to[MAXM], edgePos[MAXM], edgeCnt;
bool used[MAXM];
int ans[MAXN], ansCnt;
int stackNode[MAXM], stackEdge[MAXM], topS, topE;
int path[MAXM], pathLen;
int curHead[MAXN];

void addEdge(int u, int v, int pos) {
    edgeCnt++;
    nxt[edgeCnt] = head[u];
    to[edgeCnt] = v;
    edgePos[edgeCnt] = pos;
    head[u] = edgeCnt;
    edgeCnt++;
    nxt[edgeCnt] = head[v];
    to[edgeCnt] = u;
    edgePos[edgeCnt] = pos;
    head[v] = edgeCnt;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

        for (int i = 1; i <= n; i++) cntA[i] = cntB[i] = 0;
        for (int i = 1; i <= n; i++) {
            cntA[a[i]]++;
            cntB[b[i]]++;
        }
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if ((cntA[i] + cntB[i]) % 2 != 0) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }

        for (int i = 1; i <= n; i++) head[i] = 0;
        edgeCnt = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] != b[i]) {
                addEdge(a[i], b[i], i);
            }
        }

        for (int i = 1; i <= edgeCnt; i++) used[i] = false;
        ansCnt = 0;

        // ¸´ÖÆ head µ½ curHead
        for (int i = 1; i <= n; i++) curHead[i] = head[i];

        for (int i = 1; i <= n; i++) {
            if (curHead[i] != 0) {
                topS = 0;
                topE = 0;
                stackNode[topS++] = i;
                pathLen = 0;

                while (topS > 0) {
                    int u = stackNode[topS - 1];
                    if (curHead[u] != 0) {
                        int e = curHead[u];
                        curHead[u] = nxt[e];
                        if (!used[e]) {
                            used[e] = used[e ^ 1] = true;
                            stackNode[topS++] = to[e];
                            stackEdge[topE++] = e;
                        }
                    } else {
                        topS--;
                        if (topS > 0) {
                            int e = stackEdge[--topE];
                            path[pathLen++] = edgePos[e];
                        }
                    }
                }

                for (int j = 0; j < pathLen; j += 2) {
                    ans[ansCnt++] = path[j];
                }
            }
        }

        printf("%d\n", ansCnt);
        if (ansCnt > 0) {
            for (int i = 0; i < ansCnt; i++) {
                if (i > 0) printf(" ");
                printf("%d", ans[i]);
            }
            printf("\n");
        } else {
            printf("\n");
        }
    }
    return 0;
}
