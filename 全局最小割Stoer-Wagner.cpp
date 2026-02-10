#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=605;
int n,m,g[N][N],dis[N],fa[N],s,t,res=1e9;
bool inA[N],alive[N];
int cal(int &s,int &t){
	for(int i=1;i<=n;i++){
		inA[i]=0;
		dis[i]=0;
	}
	int k,maxd,lstd=0;
	for(int i=1;i<=n;i++){
		k=maxd=-1;
		for(int j=1;j<=n;j++){
			if(alive[j]&&!inA[j]&&dis[j]>maxd){
				maxd=dis[j];
				k=j;
			}
		}
		if(k==-1){
			return lstd;
		}
		inA[k]=1;
		s=t,t=k;
		lstd=maxd;
		for(int j=1;j<=n;++j){
			if(alive[j]&&!inA[j]){
				dis[j]+=g[k][j];
			}
		}
	}
	return maxd;
}
int Find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=Find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		g[u][v]+=w;
		g[v][u]+=w;
		int x=Find(u),y=Find(v);
		if(x!=y){
			fa[x]=y;
		}
	}
	int rt=Find(1);
	for(int i=2;i<=n;i++){
		if(Find(i)!=rt){
			cout<<0<<endl;
			return 0;
		}
	}
	for(int i=1;i<=n;++i){
		alive[i]=1;
	}
	for(int i=1;i<n;i++){
		res=min(res,cal(s,t));
		alive[s]=0;
		for(int j=1;j<=n;++j){
			if(alive[j]){
				g[t][j]=(g[j][t]+=g[s][j]);
			}
		}
	}
	cout<<res<<'\n';
	return 0;
}

