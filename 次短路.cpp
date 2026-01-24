#include <bits/stdc++.h>
using namespace std;
int n,m,tot=1,ver[1000010],hed[1000010],nxt[1000010],pre[1000010];
int vis[1000010];
double dis[1000010],edg[1000010];
struct pot{
	int x,y;
}t[1000010];
double ask(pot a,pot b){
	return sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x));
}
void add(int a,int b,double c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
void pre_dijkstra(){
	priority_queue<pair<double,int> >q;
	for(int i=1;i<=n;i++){
		dis[i]=1e9;
	}
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]>dis[u]+edg[i]){
				dis[v]=dis[u]+edg[i];
				pre[v]=i;
				if(!vis[v]){
					q.push({-dis[v],v});
				}
			}
		}
	}
}
void dijkstra(int rd){
	priority_queue<pair<int,int> >q;
	for(int i=1;i<=n;i++){
		dis[i]=1e9;
		vis[i]=0;
	}
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]>dis[u]+edg[i]&&i!=rd&&(i^1)!=rd){
				dis[v]=dis[u]+edg[i];
				if(!vis[v]){
					q.push({-dis[v],v});
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>t[i].x>>t[i].y;
	}
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b,ask(t[a],t[b]));
		add(b,a,ask(t[a],t[b]));
	}
	pre_dijkstra();
	int x=n;
	double ans=1e9;
	while(x!=1){
		int rd=pre[x];
		//cout<<rd<<endl;
		dijkstra(rd);ans=min(ans,dis[n]);
		x=ver[pre[x]^1];
	}
	if(ans==1e9){
		cout<<-1;
		return 0;
	}
	cout<<fixed<<setprecision(2)<<ans;
} 
/*
给出 n 个点的坐标，其中第一个为起点，最后一个为终点，并给出哪些位置点是相连的。
从出发点到达终点，请求第二最短路径长度。
特别地，选取的第二短路径不会重复经过同一个点，
即使可能重复走过同一个点多次路程会更短。

输入格式
第一行是两个整数 n(1≤n≤200) 和 m(1≤m≤10000)，表示一共有 n 个点和 m 条路，
以下 n 行每行两个数 x y, 代表第 i 个点的坐标，再往下的 m 行每行两个整数 p q 
，表示两个点之间有一条路，数据没有重边，可能有自环。
输出格式
只有一行包含一个数，为第二最短路线的距离（保留两位小数），
如果存在多条第一短路径，则答案就是第一最短路径的长度；
如果不存在第二最短路径，输出 -1。

输入 #1
3 3
0 0
1 1
0 2
1 2
1 3
2 3

输出 #1
2.83

*/
