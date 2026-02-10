#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=155,M=3005,inf=1e18;
int T,n,m,Q,hed[N],ver[M<<1],nxt[M<<1],edg[M<<1],tot=1,s,t,ans;
int dis[N],now[N],rs[N],rs1[N],rs2[N];
queue<pair<int,int> >q;
struct edge{
	int v,w;
};
vector<edge> qwe[N];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
int bfs(){
	for(int i=1;i<=n;i++){
		dis[i]=0;
	}
	queue<int>q;
	q.push(s);
	dis[s]=1;
	now[s]=hed[s];
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if((!edg[i])||dis[v]){
				continue;
			}
			q.push(v);
			dis[v]=dis[u]+1;
			now[v]=hed[v];
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
	int i,k,rest=flow;
	for(i=now[u];i;i=nxt[i]){
		int v=ver[i];
		if((!edg[i])||(dis[v]!=dis[u]+1)){
			continue;
		}
		k=dinic(v,min(edg[i],rest));
		if(!k){
			dis[v]=0;
			continue;
		}
		edg[i]-=k;
		edg[i^1]+=k;
		q.push(make_pair(i,k));
		rest-=k;
	}
	now[u]=i;
	return flow-rest;
}
int solve(int u,int v){
	s=u,t=v;
	int maxflow=0,flow=0;
	while(bfs()){
		while(flow=dinic(s,inf)){
			maxflow+=flow;
		}
	}
	while(!q.empty()){
		pair<int,int> res=q.front();
		q.pop();
		edg[res.first]+=res.second;
		edg[res.first^1]-=res.second;
	}
	return maxflow;
}
void build(int l,int r){
	int m1=0,m2=0;
	if(l==r){
		return;
	}
	int ans=solve(rs[l],rs[l+1]);
	qwe[rs[l]].push_back({rs[l+1],ans});
	qwe[rs[l+1]].push_back({rs[l],ans});
	for(int i=l;i<=r;i++){
		if(dis[rs[i]]!=0){
			rs1[++m1]=rs[i];
			continue;
		}
		rs2[++m2]=rs[i];
	}
	for(int i=1;i<=m1;i++){
		rs[i+l-1]=rs1[i];
	}
	for(int i=1;i<=m2;i++){
		rs[i+l+m1-1]=rs2[i];
	}
	build(l,l+m1-1);
	build(l+m1,r);
}
void query(int u,int f,int mx,int mn,int qr){
	for(int i=0;i<qwe[u].size();i++){
		int v=qwe[u][i].v,w=qwe[u][i].w;
		if(f==v){
			continue;
		}
		if(v<mx&&min(mn,w)<=qr){
			ans++;
		}
		query(v,u,mx,min(mn,w),qr);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			rs[i]=i;
		}
		for(int i=1;i<=m;i++){
			int a,b,c;
			cin>>a>>b>>c;
			add(a,b,c);
			add(b,a,c);
		}
		build(1,n);
		cin>>Q;
		while(Q--){
			int qr;
			cin>>qr;
			ans=0;
			for(int i=2;i<=n;i++){
				query(i,0,i,inf,qr);
			}
			cout<<ans<<endl;
		}
		for(int i=1;i<=n;i++){
			hed[i]=0;
		}
		tot=1;
		for(int i=1;i<=n;i++){
			qwe[i].clear();
		}
		cout<<endl;
	}
	return 0;
}

