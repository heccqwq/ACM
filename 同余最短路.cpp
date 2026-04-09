#include <bits/stdc++.h>
#define int long long
const int inf=1e16;
using namespace std;
int h,x,y,z,tot,ver[1000010],hed[1000010],nxt[1000010],edg[1000010];
int vis[1000010],dis[1000010];
void add(int u,int v,int w){
	ver[++tot]=v,nxt[tot]=hed[u],hed[u]=tot,edg[tot]=w;
}
void spfa(int s){
	queue<int> q;
	dis[s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]>dis[u]+edg[i]){
				dis[v]=dis[u]+edg[i];
				if(!vis[v]){
					q.push(v);
				}
			}
		}
	}
}
signed main(){
    ios::sync_with_stdio(0);
	cin>>h>>x>>y>>z;
	h--;
	for(int i=0;i<x;i++){
		dis[i]=inf;
		add(i,(i+y)%x,y);
		add(i,(i+z)%x,z);
	}
	spfa(0);
	int ans=0;
	for(int i=0;i<x;i++){
		if(dis[i]<=h&&dis[i]!=inf){
			ans+=(h-dis[i])/x+1;
		}
	}
	cout<<ans;
	return 0;
}
/*
给定上界H，三个正整数x，y，z，
求区间[0,H-1]可以由ax+by+cz的式子得到的不同数的个数
*/
