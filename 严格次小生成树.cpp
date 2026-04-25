#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9+7;
struct st{
    int x,y,z;
}kr[1000010];
int n,m,rt,cnt,tot,q,anz,nxt[1000010],ver[1000010],hed[1000010],edg[1000010];
int fa[1000010],f[1000010][21],dep[1000010],sz[1000010],an[1000010][21];
int an1[1000010][21],l[1000010],ans=inf;
void add(int x,int y,int z){
	ver[++tot]=y,nxt[tot]=hed[x],hed[x]=tot,edg[tot]=z;
}
bool cmp(st a,st b){
    return a.z<b.z;
}
int Find(int x){
    if(x==fa[x]){
    	return x;
	}
    return fa[x]=Find(fa[x]);
}
void kruskal(){
    sort(kr+1,kr+1+m,cmp);
    for(int i=1;i<=m;i++){
        if(kr[i].x==kr[i-1].x&&kr[i].y==kr[i-1].y||
		kr[i].x==kr[i-1].y&&kr[i].y==kr[i-1].x){
			l[i]=1;
			continue;
		}
        int fx=Find(kr[i].x),fy=Find(kr[i].y);
        if(fx!=fy){
            fa[fx]=fy;
            cnt++;
			l[i]=1;
			anz+=kr[i].z;
            add(kr[i].x,kr[i].y,kr[i].z);
            add(kr[i].y,kr[i].x,kr[i].z);
        }
        /*if(cnt==n-1){
        	return ;
		}*/
    }
}
void dfs(int x,int fa,int y){
	dep[x]=dep[fa]+1;
	f[x][0]=fa;an[x][0]=y;an1[x][0]=0;
	for(int i=1;(1<<i)<=dep[x];i++){
		f[x][i]=f[f[x][i-1]][i-1];
		an[x][i]=max(an[f[x][i-1]][i-1],an[x][i-1]);
		int mx=max(an1[f[x][i-1]][i-1],an1[x][i-1]);
		int mn=min(an[x][i-1],an[f[x][i-1]][i-1]);
		an1[x][i]=max(mx,(an[x][i-1]==an[f[x][i-1]][i-1])?0:mn);
	}	
	for(int i=hed[x];i;i=nxt[i]){
		int v=ver[i];
		if(v!=fa){
			dfs(v,x,edg[i]);
		}
	}
}
int lca(int x,int y,int z){
	if(dep[x]<dep[y]){
		swap(x,y);
	}
	int d=dep[x]-dep[y],ans=0;
	for(int i=0;(1<<i)<=d;i++){
		if((1<<i)&d){
			ans=max(ans,(an[x][i]==z?an1[x][i]:an[x][i]));
			x=f[x][i];
		}
	}
	if(x==y){
		return ans;
	}
	for(int i=log2(dep[x]);i>=0;i--){
		if(f[x][i]!=f[y][i]){
			int mx=max(an[x][i],an[y][i]);
			ans=max(mx==z?an1[x][i]:mx,ans);
			x=f[x][i];
			y=f[y][i];
		}
	}
	int mx=max(an[x][0],an[y][0]);
	return (max(mx==z?max(max(an1[x][0],an1[y][0]),ans):mx,ans));
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
    for(int i=1;i<=m;i++){
    	scanf("%lld%lld%lld",&kr[i].x,&kr[i].y,&kr[i].z);
	}
    kruskal();
	for(int i=1;i<=n;i++){
		if(!dep[i]){
			dfs(i,0,0);
		}
	}
    for(int i=1;i<=m;i++){
    	int x;
        if(!l[i]){
        	if(kr[i].x==kr[i].y){
        		continue;
			} 
            x=lca(kr[i].x,kr[i].y,kr[i].z);
            if(kr[i].z-x){
            	ans=min(ans,kr[i].z-x);
			}
        }
	}
    printf("%lld",ans+anz);
    return 0;
}
/*
严格次小生成树的边权之和一定要比最小生成树的小，即Σw次>Σw最

*/
