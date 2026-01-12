#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,s,t,tot=1,ver[1000010],hed[100010],nxt[1000010],ans,maxflow;
int edg[1000010],cost[1000010],dis[100010],incf[1000010];
int inq[1000010],pre[100010];
void add(int a,int b,int c,int v){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c,cost[tot]=v;
	ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0,cost[tot]=-v;
}
bool spfa(){
	queue<int> q;
	memset(inq,0,sizeof(inq));
	for(int i=1;i<=n;i++){
		dis[i]=1e9;
	}
	q.push(s);
	inq[s]=1;
	incf[s]=1e9;
	dis[s]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(!edg[i]){
				continue;
			}
			if(dis[v]>dis[u]+cost[i]){
				dis[v]=dis[u]+cost[i];
				pre[v]=i;
				incf[v]=min(incf[u],edg[i]);
				if(!inq[v]){
					q.push(v);
				}
			}
		}
	}
	if(dis[t]!=1e9){
		return 1;
	}
	return 0;
}
void Update(){
	int x=t;
	while(x!=s){
		int i=pre[x];
		edg[i]-=incf[t];
		edg[i^1]+=incf[t];
		x=ver[i^1];
	}
	ans+=dis[t]*incf[t];
	maxflow+=incf[t];
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int a,b,c,v;
		cin>>a>>b>>c>>v;
		add(a,b,c,v);
	}
	while(spfa()){
		Update();
	}
	cout<<maxflow<<" "<<ans;
}
