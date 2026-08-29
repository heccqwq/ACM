#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e17;
int n,m,s,t,tot=1,ver[1000100],nxt[1000100],vis[1000100],h[1000100],ans,maxflow;
int edg[1000100],cost[1000100],hed[1000100],dis[1000100],cur[1000100];
void add(int a,int b,int c,int v){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c,cost[tot]=v;
	ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0,cost[tot]=-v;
}
void spfa(){
	for(int i=1;i<=n;i++){
		h[i]=inf;
	}
	queue<int> q;
	q.push(s);
	vis[s]=1;
	h[s]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(edg[i]&&h[v]>h[u]+cost[i]){
				h[v]=h[u]+cost[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
bool dijkstra(){
	for(int i=1;i<=n;i++){
		dis[i]=inf,vis[i]=0;
	}
	priority_queue<pair<int,int> >q;
	q.push({0,s});
	dis[s]=0;
	while(!q.empty()){
		int u=q.top().second;
		cur[u]=hed[u];
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(edg[i]&&dis[v]>dis[u]+cost[i]+h[u]-h[v]){
				dis[v]=dis[u]+cost[i]+h[u]-h[v];
				q.push({-dis[v],v});
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int flow){
	if(u==t){
		return flow;
	}
	int i,rest=flow;
	vis[u]=1;
	for(i=cur[u];i;i=nxt[i]){
		int v=ver[i];
		if(h[v]!=h[u]+cost[i]||(!edg[i])||vis[v]){
			continue;
		}
		int k=dfs(v,min(rest,edg[i]));
		edg[i]-=k;
		edg[i^1]+=k;
		rest-=k;
		ans+=k*cost[i];
		if(rest==0){
			break;
		}
	}
	cur[u]=i;
	vis[u]=0;
	return flow-rest;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int u,v,w,c;
		cin>>u>>v>>w>>c;
		add(u,v,w,c);
	}
	spfa();
	while(dijkstra()){
		for(int i=1;i<=n;i++){
			h[i]+=dis[i];
			vis[i]=0;
		}
		maxflow+=dfs(s,inf);
	}
	cout<<maxflow<<" "<<ans;
	return 0;
}
