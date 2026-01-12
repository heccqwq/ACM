#include <cstring>
#include <iostream>
#include <queue>
#define int long long
using namespace std;
const int inf=1e9;
long long tot,ver[100010],nxt[100010],edg[100010],hed[100010],vis[100010];
long long n,m,cnt[100010];
long long h[100010],dis[100010];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
bool spfa(int s){
	queue<int> q;
	memset(h,63,sizeof(h));
	h[s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
    	int u=q.front();
    	q.pop();
    	vis[u]=0;
    	for (int i=hed[u];i;i=nxt[i]){
      		int v=ver[i];
      		if(h[v]>h[u]+edg[i]){
        		h[v]=h[u]+edg[i];
        		if(!vis[v]){
          			vis[v]=1;
          			q.push(v);
          			cnt[v]++;
          			if(cnt[v]>=n+1){
						return 0;
          			}
        		}
      		}
    	}
  	}
	return 1;
}
void dijkstra(int s){
	priority_queue<pair<int,int> > q;
	for (int i=1;i<=n;i++){
		dis[i]=inf;
	}
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
    	int u=q.top().second;
    	q.pop();
    	if(vis[u]){
			continue;
    	}
    	vis[u]=1;
    	for(int i=hed[u];i;i=nxt[i]){
    		int v=ver[i];
    			if(dis[v]>dis[u]+edg[i]) {
        		dis[v]=dis[u]+edg[i];
        		if(!vis[v]){
					q.push(make_pair(-dis[v],v));
        		}
    		}
    	}
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for (int i=1;i<=m;i++){
    	int u,v,w;
    	cin>>u>>v>>w;
    	add(u,v,w);
	}
	for(int i=1;i<=n;i++){
		add(0,i,0);
	}
	if(!spfa(0)){
    	cout<<-1<<endl;
    	return 0;
	}
	for(int u=1;u<=n;u++){
		for (int i=hed[u];i;i=nxt[i]){
			edg[i]+=h[u]-h[ver[i]];
		}
	}
	for(int i=1;i<=n;i++){
    	dijkstra(i);
    	long long ans=0;
    	for(int j=1;j<=n;j++){
    		if(dis[j]==inf){
				ans+=j*inf;
    		}
    		else{
				ans+=j*(dis[j]+h[j]-h[i]);
    		} 	
    	}
    	cout<<ans<<endl;
	}
}
