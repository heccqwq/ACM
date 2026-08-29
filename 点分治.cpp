#include <bits/stdc++.h>
using namespace std;
const int inf=1e9+7;
int n,m,ver[2000010],edg[2000010],nxt[2000010],hed[2000010];
int vis[2000010],siz[2000010],exist[20000010],dis[2000010],tot;
int tmp[2000010],cnt,query[1010],ans[1010],cntt;
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(vis[v]||v==fa){
			continue;
		}
		dfs1(v,u);
		siz[u]+=siz[v];
	}
	return;
}
void dfs2(int u,int fa,int root,int& minn,int& g){ 
	int mink=siz[root]-siz[u];
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(vis[v]||v==fa){
			continue; 
		}
		mink=max(mink,siz[v]);
		dfs2(v,u,root,minn,g);
	}
	if(mink<minn){
		minn=mink;
		g=u;
	}
	return;
}
void dfs3(int u,int fa,int dep){
	if(dep<=1e7){
		tmp[++cntt]=dep;
	}
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(vis[v]||v==fa){
			continue;
		}
		dfs3(v,u,dep+edg[i]);
	}
	return;
}
void solve(int u){
	cnt=0;
	cntt=0;
	dfs1(u,0);   
	int minn=inf,g;
	dfs2(u,0,u,minn,g);
	vis[g]=1;
	exist[0]=1;
	dis[++cnt]=0;
	for(int e=hed[g];e;e=nxt[e]){
		int v=ver[e];
		if(vis[v]){
			continue;
		}
		cntt=0;
		dfs3(v,g,edg[e]);
		for(int i=1;i<=cntt;i++){
			for(int j=1;j<=m;j++){
				if(query[j]-tmp[i]>=0){
					ans[j]|=exist[query[j]-tmp[i]];
				}
			}
		}
		for(int i=1;i<=cntt;i++){
			dis[++cnt]=tmp[i];
			if(tmp[i]<=1e7){
				exist[tmp[i]]=1;
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		if(dis[i]<=1e7){
			exist[dis[i]]=0; 
		}
	}
	for(int i=hed[g];i;i=nxt[i]){
		int v=ver[i];
		if(!vis[v]){
			solve(v);
		}
	}
	return;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);   
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&query[i]);
	}
	solve(1);
    for(int i=1;i<=m;i++){
    	puts(ans[i]?"AYE":"NAY");
	}
    return 0;
}
/*
给定一棵有 n 个点的树，询问树上距离为 k 的点对是否存在。

输入格式
第一行两个数 n,m。
第 2 到第 n 行，每行三个整数 u,v,w，代表树上存在一条连接 u 和 v 边权为 w 的路径。
接下来 m 行，每行一个整数 k，代表一次询问。

输出格式
对于每次询问输出一行一个字符串代表答案，存在输出 AYE，否则输出 NAY。
*/
