#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=(1<<31)-1;
int n,m,ver[1000010],hed[1000010],nxt[1000010],edg[1000010],tot=1;
int vis[1000010],dis[1000010],s;
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
void dijkstra(){
	priority_queue<pair<int,int> > q;
	for(int i=1;i<=n;i++){
		dis[i]=inf;
	}
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]>dis[u]+edg[i]){
				dis[v]=dis[u]+edg[i];
				if(!vis[v]){
					q.push(make_pair(-dis[v],v));
				}
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	dijkstra();
	for(int i=1;i<=n;i++){
		cout<<dis[i]<<" ";
	}
}
