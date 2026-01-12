#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node{
	int u,v;
}edg[1000010];
int n,m,tot,ver[1000010],hed[1000010],nxt[1000010],deg[1000010];
int vis[1000010],ans;
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		edg[i].u=a,edg[i].v=b;
		deg[a]++,deg[b]++;
	}
	for(int i=1;i<=m;i++){
		int a=edg[i].u,b=edg[i].v;
		if(deg[a]==deg[b]){
			if(a>b){
				add(b,a);
				continue;
			}
			add(a,b);
			continue;
		}
		if(deg[a]>deg[b]){
			add(b,a);
			continue;
		}
		add(a,b);
	}
	for(int u=1;u<=n;u++){
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			vis[v]=1;
		}
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			for(int j=hed[v];j;j=nxt[j]){
				int w=ver[j];
				if(vis[w]){
					ans++;
				}
			}
		}
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			vis[v]=0;
		}
	}
	cout<<ans;
}
