#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9;
int n,m,s,t,tot=1,ver[1000010],hed[1000010],nxt[1000010],edg[1000010];
int now[1000010],d[1000010],maxflow,flow;
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
	ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0;
}
bool bfs(){
	for(int i=1;i<=n;i++){
		d[i]=0;
	}
	queue<int> q;
	q.push(s);
	now[s]=hed[s];
	d[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop(); 
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if((!edg[i])||d[v]){
				continue;
			}
			d[v]=d[u]+1;
			now[v]=hed[v];
			q.push(v);
		} 
	}
	if(d[t]){
		return 1;
	}
	return 0;
}
int dinic(int u,int flow){
	if(u==t){
		return flow;
	}
	int i,rest=flow;
	for(i=now[u];i;i=nxt[i]){
		int v=ver[i];
		if(d[v]!=d[u]+1||edg[i]==0){
			continue;
		}
		int k=dinic(v,min(edg[i],rest));
		if(!k){
			d[v]=0;
			continue;
		}
		rest-=k;
		edg[i]-=k;
		edg[i^1]+=k;
	}
	return flow-rest;
} 
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	while(bfs()){
		while(flow=dinic(s,inf)){
			maxflow+=flow;
		}
	}
	cout<<maxflow;
}
