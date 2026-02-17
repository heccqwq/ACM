#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ver[5000010],hed[5000010],nxt[5000010],dfn[5000010],low[5000010];
int cnt,sm,tot=1,rt,brg[5000010],vis[1000010];
vector<int> ecc[500010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u,int in_edg){
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				brg[i]=brg[i^1]=1; 
			}
		}
		else if(in_edg!=(i^1)){
			low[u]=min(low[u],dfn[v]);
		}
	}
}
void dfs(int u){
	vis[u]=1;
	ecc[sm].push_back(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(brg[i]||vis[v]){
			continue;
		}
		dfs(v);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		if(a==b){
			continue;
		}
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,0);
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}
		sm++;
		dfs(i);
		if(ecc[sm].size()==0){
			sm--;
		}
	}
	cout<<sm<<endl;
	for(int i=1;i<=sm;i++){
		cout<<ecc[i].size()<<" ";
		for(int j=0;j<ecc[i].size();j++){
			cout<<ecc[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
