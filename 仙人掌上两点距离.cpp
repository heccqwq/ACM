#include <bits/stdc++.h>
using namespace std;
struct Edge{
	int ver,nxt,edg;
}e[5000050],e2[5000050];
int dfn[5000050],low[5000050],cnt,w[5000050],dis[5000050],dis2[5000050],r[5000050],sm;
int n,m,q,hed[1000010],tot,hedd[5000050],tott,p[500050][22],d[5000050];
stack<int> s;
void add(int a,int b,int c){
	e[++tot].ver=b,e[tot].nxt=hed[a],e[tot].edg=c,hed[a]=tot;
}
void addd(int a,int b,int c){
	e2[++tott].ver=b,e2[tott].nxt=hedd[a],e2[tott].edg=c,hedd[a]=tott;
}
void tarjan(int u,int fa){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	for(int i=hed[u];i;i=e[i].nxt){
		int v=e[i].ver;
		if(v==fa){
			continue;
		}
		if(!dfn[v]){
			w[v]=e[i].edg;
			dis[v]=dis[u]+e[i].edg;
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++sm;
				int x=s.top();
				r[sm]=w[x]+dis[x]-dis[u];
				do{
					x=s.top();
					s.pop();
					int tmp=min(dis[x]-dis[u],r[sm]-dis[x]+dis[u]);
					addd(x,sm,tmp);
					addd(sm,x,tmp);
				}while(x!=v);
				addd(u,sm,0);
				addd(sm,u,0);
			}
		}
		else if(dfn[v]<dfn[u]){
			w[u]=e[i].edg;
			low[u]=min(low[u],dfn[v]);
		}
	}
}
void dfs(int u,int fa){
	p[u][0]=fa;
	d[u]=d[fa]+1;
	for(int i=1;i<20;i++){
		p[u][i]=p[p[u][i-1]][i-1];
	}
	for(int i=hedd[u];i;i=e2[i].nxt){
		int v=e2[i].ver;
		if(v==fa){
			continue;
		}
		dis2[v]=dis2[u]+e2[i].edg;
		dfs(v,u);
	}
}
pair<int,int> lca(int x,int y){
	if(d[x]<d[y]){
		swap(x,y);
	}
	for(int dt=d[x]-d[y],i=0;dt;dt>>=1,i++){
		if(dt&1){
			x=p[x][i];
		}
	}
	if(x==y){
		return make_pair(x,-1);
	}
	for(int i=20;~i;i--){
		if(p[x][i]!=p[y][i]){
			x=p[x][i];
			y=p[y][i];
		}
	}
	if(p[x][0]<=n){
		return make_pair(p[x][0],-1);
	}
	return make_pair(x,y);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>q;
	sm=n;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	tarjan(1,0);
	dfs(1,0);
	while(q--){
		int u,v;
		cin>>u>>v;
		pair<int,int> pi=lca(u,v);
		if(pi.second==-1){
			cout<<dis2[u]+dis2[v]-2*dis2[pi.first]<<endl;
		}
		else{
			int tmp=min(abs(dis[pi.first]-dis[pi.second]),
				r[p[pi.first][0]]-abs(dis[pi.first]-dis[pi.second]));
			cout<<dis2[u]+dis2[v]-dis2[pi.first]-dis2[pi.second]+tmp<<endl;
		}
	}
	return 0;
}
/*
给你一个有 n 个点和 m 条边的仙人掌图，和 q 组询问
每次询问两个点 u,v，求两点之间的最短路。
保证输入数据没有重边。
*/

