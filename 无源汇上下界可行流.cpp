#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s,t,tot=1,maxflow,dis[100010],now[100010],V[100010],flow;
int hed[100010],ver[100010],nxt[100010],edg[100010],ppp[100010];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
	ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0;
}

bool bfs(){
	queue<int>q;
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	now[s]=hed[s];
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]||(!edg[i])){
				continue;
			}
			now[v]=hed[v];
			dis[v]=dis[u]+1;
			q.push(v);
			if(v==t){
				return 1;
			}
		}
	}
	return 0;
}
int dinic(int u,int flow){
	if(u==t){
		return flow;
	}
	int i,rest=flow;
	for(i=now[u];i&&rest;i=nxt[i]){
		int v=ver[i];
		if(dis[v]!=dis[u]+1||(!edg[i])){
			continue;
		}
		int k=dinic(v,min(rest,edg[i]));
		if(!k){
			dis[v]=0;	
		}
		edg[i]-=k;
		edg[i^1]+=k;
		rest-=k;
	}
	now[u]=i;
	return flow-rest;
}
signed main(){
	cin>>n>>m;
	s=0,t=n+1;
	for(int i=1;i<=m;i++){
		int u,v,p,q;
		cin>>u>>v>>p>>q;
		add(u,v,q-p);
		V[u]-=p,V[v]+=p;
		ppp[i]=p;
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(V[i]>0){
			add(s,i,V[i]);
			sum+=V[i];
		}
		if(V[i]<0){
			add(i,t,-V[i]);
		}
	}
	while(bfs()){
		while(flow=dinic(s,1e18)){
			maxflow+=flow;
		}
	}
	if(maxflow<sum){
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=3;i<=2*m+1;i+=2){
		cout<<edg[i]+ppp[i/2]<<endl;
	}
	return 0;
}

