#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,tot=1,ver[1000010],hed[1000010],nxt[1000010],edg[1000010],vis[1000010];
int dis1[1000010],disn[1000010],pac[1000010],loc[1000010];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
void dijkstra(){
	for(int i=1;i<=n;i++){
		dis1[i]=1e16;
	}
	priority_queue<pair<int,int> >q;
	dis1[1]=0;
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
			if(dis1[v]>dis1[u]+edg[i]){
				dis1[v]=dis1[u]+edg[i];
				pac[v]=i;
				if(!vis[v]){
					q.push({-dis1[v],v});
				}
			}
		}
	}
}
void dijkstraa(){
	for(int i=1;i<=n;i++){
		disn[i]=1e16;
		vis[i]=0;
	}
	priority_queue<pair<int,int> >q;
	disn[n]=0;
	q.push({0,n});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(disn[v]>disn[u]+edg[i]){
				disn[v]=disn[u]+edg[i];
				if(!vis[v]){
					q.push({-disn[v],v});
				}
			}
		}
	}
}
void solve(){
	int x=n;
	int cnt=0;
	while(x!=1){
		cnt++;
		loc[pac[x]]=1;
		loc[pac[x]^1]=1;
		x=ver[pac[x]^1];
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	int a,b,c;
    	cin>>a>>b>>c;
    	add(a,b,c);
    	add(b,a,c);
	}
	dijkstra();
	if(!vis[n]){
		cout<<-1;
		return 0;
	}
	solve();
	dijkstraa();
	int ans=1e16,sm=dis1[n];
	for(int i=2;i<=tot;i++){
		if(loc[i]){
			continue;
		}
		int u=ver[i],v=ver[i^1];
		int cnt=min(dis1[u]+disn[v]+edg[i],disn[u]+dis1[v]+edg[i]);
		ans=min(ans,cnt);
	}
	if(ans==1e16){
		 cout<<-1<<endl;
		 return 0;
	}
	cout<<sm+ans;
}
/*
亚太地区有 n 个城市编号从1到 n.2024年ICPC亚洲及太平洋锦标赛在河内（即城市 n）举行。
有 m 条双向道路，编号从 1 到 m，连接着一些城市对。道路 i 连接城市 u和 v 
 ，任一方向的旅行时间为 t 。每条道路连接不同的城市，且不同的道路连接不同的城市对。
你居住在城市 1。你希望通过一系列道路前往城市 n ，然后再通过一系列道路返回城市 1。
走同一条路线很无聊，所以你希望两次行程的路线是不同的。
如果两条路线所经过的不同道路的集合是不同的，那么这两条路线就被认为是不同的。
在每次行程中，可以多次经过同一个城市或走同一条道路。
在到达目的地城市（即城市 1 或城市 n）后，也可以继续行进。
行程时间是行程中所经过道路的旅行时间之和。
如果一条道路在行程中被多次经过，那么它的旅行时间也会被相应地计算多次。
请确定满足上述要求的两次行程的最小总旅行时间，或者指出无法满足要求。

输入 #1
3 2
1 2 10
1 3 5
输出 #1
30

输入 #2
4 4
1 2 3
2 4 2
1 3 3
3 4 4
输出 #2
12

输入 #3
3 1
1 2 1000
输出 #3
-1
*/
