#include <bits/stdc++.h>
using namespace std;
int n,m,tot,ver[1000010],hed[1000010],nxt[1000010],top[1000010];
int dep[1000010],son[1000010],fa[1000010],siz[1000010],s;
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void dfs1(int u,int faa){
	siz[u]=1,fa[u]=faa,dep[u]=dep[faa]+1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==faa){
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
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
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
	cin>>n>>m>>s;
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	dfs1(s,0);
	dfs2(s,s);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		cout<<lca(a,b)<<endl;
	}
}
