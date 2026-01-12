#include <bits/stdc++.h>
using namespace std;
int n,m,tot=1,nxt[4000010],hed[4000010],ver[4000010],dfn[4000010];
int brg[4000010],low[4000010],ans,cnt,vis[4000010];
vector<int> stk[100010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u,int in_edg){
	dfn[u]=low[u]=++cnt;
	//cout<<u<<endl;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				brg[i]=brg[i^1]=1;
			}
		}
		else if(i!=(in_edg^1)){
			low[u]=min(low[u],dfn[v]);
		}
	}
}
void dfs(int u){
	vis[u]=1;
	stk[ans].push_back(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(brg[i]||vis[v]){
			continue;
		}
		dfs(v);
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
			tarjan(i,0);	
		}
	}
	/*for(int i=1;i<=tot;i++){
		if(brg[i]){
			cout<<"gsdrhseh";	
		}
	}*/
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}
		ans++;
		dfs(i);
	//	cout<<ans<<" "<<stk[ans].size()<<endl;
		if(stk[ans].size()==0){
			ans--;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++){
		cout<<stk[i].size()<<" ";
		for(int k=0;k<stk[i].size();k++){
			cout<<stk[i][k]<<" ";
		}
		cout<<endl;
	}
} 
