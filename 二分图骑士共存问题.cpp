#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,tot=1,ver[5000010],hed[1000010],nxt[5000010],edg[5000010];
int d[1000010],now[1000010],blk[1010][1010],s,t,maxflow,flow;
int dv[10][10]={{-1,2},{-1,-2},{1,2},{1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};
bool check(int x,int y){
	if(x>n||y>n||x<1||y<1){
		return 0;
	}
	return 1;
}
bool bfs(){
	for(int i=1;i<=n*n+1;i++){
		d[i]=0;
	}
	d[s]=1;
	now[s]=hed[s];
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(d[v]||(!edg[i])){
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
	for(i=now[u];i&&rest;i=nxt[i]){
		int v=ver[i];
		if(d[v]!=d[u]+1||(!edg[i])){
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
	now[u]=i;
	return flow-rest;
}
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
	ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	s=0,t=n*n+1;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		blk[a][b]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(blk[i][j]){
				continue;
			}
			if((i+j)%2==0){
				add(s,(i-1)*n+j,1);
			}
			if((i+j)%2==1){
				add((i-1)*n+j,t,1);
			}
			if((i+j)%2==0){
				for(int k=0;k<=7;k++){
					int nx=i+dv[k][0],ny=j+dv[k][1];
					if(!check(nx,ny)){
						continue;
					}
					add((i-1)*n+j,(nx-1)*n+ny,inf);
				}
			}
		}
	}
	while(bfs()){
		while(flow=dinic(s,inf)){
			maxflow+=flow;
		}
	}
	cout<<n*n-m-maxflow;
}
/*
对于给定的 n×n 个方格的国际象棋棋盘和障碍标志
计算棋盘上最多可以放置多少个骑士，使得它们彼此互不攻击。
*/
