#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int T,n,m,ver[1000010],hed[1000010],edg[1000010],tot;
int nxt[1000010],cnt[1000010],dis[1000010],vis[1000010];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
bool spfa(){
	queue<int> q;
	q.push(1);
	vis[1]=1;
	dis[1]=0;
	while(!q.empty()){
		int u=q.front();
		vis[u]=0;
		q.pop();
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if(dis[v]>dis[u]+edg[i]){
				dis[v]=dis[u]+edg[i];
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
					cnt[v]++;
					if(cnt[v]>n){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		memset(ver,0,sizeof(ver));
		memset(hed,0,sizeof(hed));
		memset(nxt,0,sizeof(nxt));
		memset(edg,0,sizeof(edg));
		memset(dis,0x3f3f3f3f,sizeof(dis));
		memset(vis,0,sizeof(vis));
		memset(cnt,0,sizeof(cnt));
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int a,b,c;
			cin>>a>>b>>c;
			if(c>=0){
				add(a,b,c);
				add(b,a,c);
			}
			if(c<0){
				add(a,b,c);
			}
		}
		if(spfa()){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
}
