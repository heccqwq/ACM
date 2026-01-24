#include <bits/stdc++.h>
using namespace std;
int n,m,q,tot,ver[2000010],hed[2000010],nxt[2000010],dep[2000010];
int cnt,sm,blg[2000010],dfn[2000010],low[2000010],siz[2000010];
int son[2000010],top[2000010],fa[2000010],w[2000010],dis[2000010];
stack<int> s;
vector<int> t[1000010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<=low[v]){
				sm++;
				int k=0;
				while(k!=v){
					k=s.top();
					s.pop();
					blg[k]=sm;
					t[sm].push_back(k);
					t[k].push_back(sm);
				}
				t[sm].push_back(u);
				t[u].push_back(sm);
				blg[u]=sm;
			}
		}
		else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}
void dfs1(int u,int faa){
	dep[u]=dep[faa]+1;
	fa[u]=faa;
	siz[u]=1;
	dis[u]=dis[faa]+w[u];
	for(int i=0;i<t[u].size();i++){
		int v=t[u][i];
		if(v==fa[u]){
			continue;
		}
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u]){
		dfs2(son[u],tp);
	}
	for(int i=0;i<t[u].size();i++){
		int v=t[u][i];
		if(v==fa[u]||v==son[u]){
			continue;
		}
		dfs2(v,v);
	}
}
int lca(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]]){
			a=fa[top[a]];
			continue;
		}
		b=fa[top[b]];
	}
	return dep[a]>dep[b]?b:a;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	sm=n;
	for(int i=1;i<=n;i++){
		w[i]=1;
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	dfs1(1,0);
	dfs2(1,1);
	cin>>q;
	for(int i=1;i<=q;i++){
		int u,v,ans=0;
		cin>>u>>v;
		int x=lca(u,v);
		if(x<=n){
			ans++;
		}
		ans+=dis[u]+dis[v]-dis[x]*2;
		cout<<ans<<endl;
	}
}
/*
小 c 想知道从城市 u 到城市 v 有多少个城市一定会经过，
特别地，u,v 也必须被算进去，也就是说无论如何答案不会小于 2
小 c 知道的起点和终点只有 q 种可能，
所以对于这 q 种可能，小 c 都想知道一定会经过的城市数
所有的边都是无向边，两个城市之间最多只有一条道路直接相连，
没有一条道路连接相同的一个城市。任何时候，不存在 u 和 v 满足从 u 无法到达 v
输入格式
第一行两个正整数 n,m，表示 城市数，以及道路数。
下面 m 行，每行两个不同的正整数 u,v，表示城市 u 到城市 v 之间有一条边。
然后一行一个正整数 q。
接下来 q 行，每行两个正整数 u,v 表示小 w 旅行的一种可能的路线
输出格式
输出共 q 行，每行一个正整数

输入 #1
5 6
1 2
1 3
2 3
3 4
4 5
3 5
1
1 5
输出 #1
3


*/
