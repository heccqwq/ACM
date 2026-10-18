#include <bits/stdc++.h>
using namespace std;
int n,m,tot,ver[1000010],hed[1000010],nxt[1000010],p[1000010],v[1000010];
int indeg[1000010],indeg2[1000010];
double dis[1000010];
bool vis[1000010];
void add(int a, int b, int pp, int vv){
    ver[++tot] = b, nxt[tot] = hed[a], hed[a] = tot, p[tot] = pp, v[tot] = vv;
}
bool dfs(int u,double ans){
    vis[u]=1;
    for(int i=hed[u];i;i=nxt[i]){
        int vv=ver[i];
        double w=ans*p[i]-v[i];
        if(dis[vv]>dis[u]+w){
            dis[vv]=dis[u]+w;
            if(vis[vv]){
            	return 1;
			}
            if(dfs(vv,ans)){
            	return 1;
			}
        }
    }
    vis[u]=0;
    return 0;
}
bool hasNegCycle(double ans){
    for(int i=1;i<=n;i++){
        dis[i]=vis[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(dfs(i,ans)){
        	return 1;
		}
    }
    return 0;
}
bool hasCycle(){
    queue<int> q;
    int c=0;
    for(int i=1;i<=n;i++){
        indeg2[i]=indeg[i];
        if(indeg2[i]==0){
        	q.push(i);
		}
    }
    while(!q.empty()){
        int u=q.front();
		q.pop();
        c++;
        for(int i=hed[u];i;i=nxt[i]){
        	if(--indeg2[ver[i]]==0){
        		q.push(ver[i]);
			}
		}
    }
    return c<n;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b,vv,pp;
        cin>>a>>b>>vv>>pp;
        add(a,b,pp,vv);
        indeg[b]++;
    }
    if(!hasCycle()){
        cout<<-1;
        return 0;
    }
    double l=0,r=1e9;
    for(int it=0;it<60;it++){
        double mid =(l+r)/2;
        if(hasNegCycle(mid)){
        	l=mid;
		}
        else{
        	r=mid;	
		}
    }
    cout<<fixed<<setprecision(1)<<l;
    return 0;
}
/*
N 个点，M 条路径，路径定义了两个值，Vi和 Pi，分别表示趣味度和价格。
现在想知道从任意一个点开始走过的一条回路上所有的 V 之和与 P 之和的比值的最大值。
（路线不一定包含所有的点，但是不可以存在重复的路径）。
*/
