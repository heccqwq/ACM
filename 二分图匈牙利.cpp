#include <iostream>
#include <cstring>
using namespace std;
int n,m,e,tot,ans;
int ver[50010],hed[50010],nxt[50010],match[50010];
bool vis[50010],h[5010][5010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
bool dfs(int x){
	for(int i=hed[x];i;i=nxt[i]){
		int y=ver[i];
		if(!vis[y]){
			vis[y]=1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
    ios::sync_with_stdio(0);
	cin>>n>>m>>e;
	for(int i=1;i<=e;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i))
		ans++;
	}
	cout<<ans;
}
