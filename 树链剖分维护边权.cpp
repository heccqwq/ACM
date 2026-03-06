#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,tot,ver[1000010],hed[1000010],nxt[1000010],fa[1000010],siz[1000010];
int dep[1000010],pos[1000010],son[1000010],top[1000010],edg[1000010];
int d[1000010],w[1000010],cnt;
struct SegmentTree{
	int sm,mx,mn,tag,val,l,r;
}a[1000010];
void add(int a,int b,int c){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
}
void Update(int p){
	if(a[p].tag){
		a[p*2].val*=-1;
		a[p*2+1].val*=-1;
		a[p*2].tag^=1;
		a[p*2+1].tag^=1;
		a[p*2].sm*=-1;
		a[p*2+1].sm*=-1;
		a[p].tag=0;
		swap(a[p*2].mx,a[p*2].mn);
		swap(a[p*2+1].mx,a[p*2+1].mn);
		a[p*2].mx*=-1;
		a[p*2+1].mx*=-1;
		a[p*2].mn*=-1;
		a[p*2+1].mn*=-1;
	}
	return ;
}
void dfs1(int u,int faa){
	fa[u]=faa;
	dep[u]=dep[faa]+1;
	siz[u]=1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==faa){
			continue;
		}
		d[v]=edg[i];
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	w[++cnt]=d[u];
	pos[u]=cnt;
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
void Build(int p,int l,int r){
	a[p].l=l,a[p].r=r;
	if(l==r){
		a[p].val=a[p].sm=a[p].mx=a[p].mn=w[l];
		return ;
	}
	int mid=(l+r)/2;
	Build(p*2,l,mid);
	Build(p*2+1,mid+1,r);
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	a[p].mx=max(a[p*2].mx,a[p*2+1].mx);
	a[p].mn=min(a[p*2].mn,a[p*2+1].mn);
	return ;
}
int Qsum(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		return a[p].sm;
	}
	Update(p);
	int mid=(a[p].l+a[p].r)/2,sm=0;
	if(l<=mid){
		sm+=Qsum(p*2,l,r);
	}
	if(r>mid){
		sm+=Qsum(p*2+1,l,r);
	}
	return sm;
}
int Qmax(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		return a[p].mx;
	}
	Update(p);
	int mid=(a[p].l+a[p].r)/2,mx=-1e9;
	if(l<=mid){
		mx=max(mx,Qmax(p*2,l,r));
	}
	if(r>mid){
		mx=max(mx,Qmax(p*2+1,l,r));
	}
	return mx;
}
int Qmin(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		return a[p].mn;
	}
	Update(p);
	int mid=(a[p].l+a[p].r)/2,mn=1e9;
	if(l<=mid){
		mn=min(mn,Qmin(p*2,l,r));
	}
	if(r>mid){
		mn=min(mn,Qmin(p*2+1,l,r));
	}
	return mn;
}
void change(int p,int aim,int v){
	if(a[p].l==a[p].r&&a[p].l==aim){
		a[p].mx=a[p].mn=a[p].val=a[p].sm=v;
		return ;
	}
	Update(p);
	int mid=(a[p].l+a[p].r)/2;
	if(aim<=mid){
		change(p*2,aim,v);
	}
	if(aim>mid){
		change(p*2+1,aim,v);
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	a[p].mx=max(a[p*2].mx,a[p*2+1].mx);
	a[p].mn=min(a[p*2].mn,a[p*2+1].mn);
	return ;
}
void flip(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		a[p].val*=-1;
		a[p].tag^=1;
		a[p].sm*=-1;
		swap(a[p].mx,a[p].mn);
		a[p].mx*=-1;
		a[p].mn*=-1;
		return ;
	}
	Update(p);
	int mid=(a[p].l+a[p].r)/2;
	if(l<=mid){
		flip(p*2,l,r);
	}
	if(r>mid){
		flip(p*2+1,l,r);
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	a[p].mx=max(a[p*2].mx,a[p*2+1].mx);
	a[p].mn=min(a[p*2].mn,a[p*2+1].mn);
	return ;
}
void Doflip(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			flip(1,pos[top[u]],pos[u]);
			u=fa[top[u]];
			continue;
		}
		flip(1,pos[top[v]],pos[v]);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v]){
		flip(1,pos[v]+1,pos[u]);
		return ;
	}
	flip(1,pos[u]+1,pos[v]);
	return ;
}
int Asksm(int u,int v){
	int sm=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			sm+=Qsum(1,pos[top[u]],pos[u]);
			u=fa[top[u]];
			continue;
		}
		sm+=Qsum(1,pos[top[v]],pos[v]);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v]){
		sm+=Qsum(1,pos[v]+1,pos[u]);
		return sm;
	}
	sm+=Qsum(1,pos[u]+1,pos[v]);
	return sm;
}
int Askmx(int u,int v){
	int mx=-1e9;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			mx=max(mx,Qmax(1,pos[top[u]],pos[u]));
			u=fa[top[u]];
			continue;
		}
		mx=max(mx,Qmax(1,pos[top[v]],pos[v]));
		v=fa[top[v]];
	}
	if(dep[u]>dep[v]){
		mx=max(mx,Qmax(1,pos[v]+1,pos[u]));
		return mx;
	}
	mx=max(mx,Qmax(1,pos[u]+1,pos[v]));
	return mx;
}
int Askmn(int u,int v){
	int mn=1e9;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			mn=min(mn,Qmin(1,pos[top[u]],pos[u]));
			u=fa[top[u]];
			continue;
		}
		mn=min(mn,Qmin(1,pos[top[v]],pos[v]));
		v=fa[top[v]];
	}
	if(dep[u]>dep[v]){
		mn=min(mn,Qmin(1,pos[v]+1,pos[u]));
		return mn;
	}
	mn=min(mn,Qmin(1,pos[u]+1,pos[v]));
	return mn;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	d[1]=0;
	for(int i=1;i<n;i++){
		int u,v,z;
		cin>>u>>v>>z;
		u++,v++;
		add(u,v,z);
		add(v,u,z);
	}
	dfs1(1,0);
	dfs2(1,1);
	Build(1,1,n);
	cin>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		string opt;
		cin>>opt>>u>>v;
		u++,v++;
		if(opt=="C"){
			u--;v--;
			int depa=dep[ver[u*2-1]],depb=dep[ver[u*2]];
			int p=pos[(depa>depb)?ver[u*2-1]:ver[u*2]];
			change(1,p,v);
		}
		if(opt=="N"){
			Doflip(u,v);
		}
		if(opt=="SUM"){
			cout<<Asksm(u,v)<<endl;
		}
		if(opt=="MAX"){
			cout<<Askmx(u,v)<<endl;
		}
		if(opt=="MIN"){
			cout<<Askmn(u,v)<<endl;
		}
	}
}
/*
C i w 将输入的第 i 条边权值改为 w；
N u v 将 u,v 节点之间的边权都变为相反数；
SUM u v 询问 u,v 节点之间边权和；
MAX u v 询问 u,v 节点之间边权最大值；
MIN u v 询问 u,v 节点之间边权最小值。
*/
