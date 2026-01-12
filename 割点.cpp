#include <bits/stdc++.h>
using namespace std;
int n,m,tot=1,ver[1000010],hed[1000010],nxt[1000010],cnt;
int dfn[1000010],low[1000010],root,ans,cut[1000010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u){
	int fl=0;
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				fl++;
				if(fl>1||u!=root){
					cut[u]=1;
				}
			}
		}
		else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			root=i;
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(cut[i]){
			ans++;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(cut[i]){
			cout<<i<<" ";
		}
	}
	return 0;
}
