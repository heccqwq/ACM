#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,d[1010][1010],dd[1010][1010],rk[1010][1010],val[100010];
int inf=1e17;
struct rd{
  int u,v,w;
}a[1000010];
bool cmp(int a,int b){
	return val[a]<val[b];
}
void floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
}
void solve(){
	floyd();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			rk[i][j]=j;
			val[j]=d[i][j];
		}
		sort(rk[i]+1,rk[i]+n+1,cmp);
	}
	int P=0,ansP=inf;
	for(int i=1;i<=n;i++){
		if(d[i][rk[i][n]]*2<ansP){
			ansP=d[i][rk[i][n]]*2;
			P=i;
		}
	}
	// 在边上
	int f1=0,f2=0;
	int disu=-inf,disv=-inf,ansL=inf;
	for(int i=1;i<=m;i++){
		int u=a[i].u,v=a[i].v,w=a[i].w;
		for(int p=n,j=n-1;j>=1;j--){
			if(d[v][rk[u][j]]>d[v][rk[u][p]]){
				if(d[u][rk[u][j]]+d[v][rk[u][p]]+w<ansL){
					ansL=d[u][rk[u][j]]+d[v][rk[u][p]]+w;
					f1=u,f2=v;
					disu=(d[u][rk[u][j]]+d[v][rk[u][p]]+w)/2-d[u][rk[u][j]];
					disv=w-disu;
				}
				p=j;
			}
		}
	}
	cout<<min(ansP, ansL)/2<<endl;
	// 构造最小路径生成树
	vector<pair<int,int> >pp;
	for(int i=1;i<=501;i++){
		for(int j=1;j<=501;j++){
			dd[i][j]=inf;
		}
		dd[i][i]=0;
	}
	if(ansP<=ansL){
		for(int j=1;j<=n;j++){
			for(int i=1;i<=m;i++){
				int u=a[i].u,v=a[i].v,w=a[i].w;
				if(dd[P][u]+w==d[P][v]&&dd[P][u]+w<dd[P][v]){
					dd[P][v]=dd[P][u]+w;
					pp.push_back(make_pair(u,v));
				}
				u=a[i].v,v=a[i].u,w=a[i].w;
				if(dd[P][u]+w==d[P][v]&&dd[P][u]+w<dd[P][v]){
					dd[P][v]=dd[P][u]+w;
					pp.push_back(make_pair(u,v));
				}
			}
		}
		for(int i=0;i<pp.size();i++){
			cout<<pp[i].first<<" "<<pp[i].second<<endl;
		}
	}
	else{
		d[n+1][f1]=disu;
		d[f1][n+1]=disu;
		d[n+1][f2]=disv;
		d[f2][n+1]=disv;
		a[m+1].u=n+1,a[m+1].v=f1,a[m+1].w=disu;
		a[m+2].u=n+1,a[m+2].v=f2,a[m+2].w=disv;
		n+=1;
		m+=2;
		floyd();
		P=n;
		for(int j=1;j<=n;j++){
			for(int i=1;i<=m;i++){
				int u=a[i].u,v=a[i].v,w=a[i].w;
				if(dd[P][u]+w==d[P][v]&&dd[P][u]+w<dd[P][v]){
					dd[P][v]=dd[P][u]+w;
					pp.push_back(make_pair(u,v));
				}
				u=a[i].v,v=a[i].u,w=a[i].w;
				if(dd[P][u]+w==d[P][v]&&dd[P][u]+w<dd[P][v]){
					dd[P][v]=dd[P][u]+w;
					pp.push_back(make_pair(u,v));
				}
			}
		}
		cout<<f1<<" "<<f2<<endl;
		for(int i=0;i<pp.size();i++){
			if(pp[i].first==n||pp[i].second==n){
				continue;
			}
			cout<<pp[i].first<<" "<<pp[i].second<<endl;
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=501;i++){
		for(int j=1;j<=501;j++){
			d[i][j]=inf;
		}
		d[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		w*=2;
		d[u][v]=w,d[v][u]=w;
		a[i].u=u,a[i].v=v,a[i].w=w;
	}
	solve();
	return 0;
}
