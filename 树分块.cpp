#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,tot,ver[100010],hed[100010],nxt[100010],dfn[100010],idx[100010],cnt;
int dep[100010],fa[100010],top[100010],siz[100010],son[100010],arr[100010];
int T,w[100010],x,a[100010],blg[100010],L[100010],R[100010];
bitset<40040> f[210][210],ans; // 210 > sqrt(40000) ≈ 200
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void dfs1(int u,int faa){
	dep[u]=dep[faa]+1;
	fa[u]=faa;
	siz[u]=1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==faa){
			continue;
		}
		dfs1(v,u);
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	idx[++cnt]=u;
	dfn[u]=cnt;
	a[cnt]=w[u];
	if(son[u]){
		dfs2(son[u],tp);
	}
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==fa[u]||v==son[u]){
			continue;
		}
		dfs2(v,v);
	}
}
void pre(){
	for(int i=1;i<=n;i++){
		blg[i]=(i-1)/T+1;
	}
	int num=blg[n];
	for(int i=1;i<=num;i++){
		L[i]=(i-1)*T+1;
		R[i]=min(i*T,n);
	}
	for(int i=1;i<=num;i++){
		f[i][i].reset();
		for(int j=L[i];j<=R[i];j++){
			f[i][i].set(a[j]);
		}
	}
	for(int i=1;i<=num;i++){
		for(int j=i+1;j<=num;j++){
			f[i][j]=f[i][j-1]|f[j][j];
		}
	}
}

inline void Ask(int l,int r){
	if(blg[l]==blg[r]){
		for(int i=l;i<=r;i++){
			ans.set(a[i]);
		}
		return;
	}
	if(blg[l]+1<=blg[r]-1){
		ans|=f[blg[l]+1][blg[r]-1];
	}
	for(int i=l;i<=R[blg[l]];i++){
		ans.set(a[i]);
	}
	for(int i=L[blg[r]];i<=r;i++){
		ans.set(a[i]);
	}
}

inline void Qus(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v);
		}
		Ask(dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]){
		swap(u,v);
	}
	Ask(dfn[u],dfn[v]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	T=max(1ll,(int)sqrt(n));
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		w[i]=arr[i];
	}
	sort(arr+1,arr+1+n);
	arr[0]=unique(arr+1,arr+1+n)-arr-1;
	for(int i=1;i<=n;i++){
		w[i]=lower_bound(arr+1,arr+1+arr[0],w[i])-arr;
	}
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);
	pre();
	x=0;
	while(m--){
		int u,v;
		ans.reset();
		cin>>u>>v;
		u^=x;
		Qus(u,v);
		x=ans.count();
		cout<<x<<'\n';
	}
}
/*
在线查询树上 u 到 v 的路径上有多少个不同的整数。
1≤u,v≤n≤4×104
1≤m≤1e5 ,0≤vali<2^31 
*/
