#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree{
	int l,r,sm,add;
}a[1000010];
int n,m,root,mod,tot,hed[1000010],nxt[1000010],ver[1000010],w[1000010];
int son[1000010],id[1000010],fa[1000010],cnt,dep[1000010],size[1000010];
int top[1000010],wt[1000010]; 
void add(int a,int b){
    ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void Spread(int p){
	if(a[p].add){
		a[p*2].add+=a[p].add;
		a[p*2+1].add+=a[p].add;
		a[p*2].sm+=(a[p*2].r-a[p*2].l+1)*a[p].add;
		a[p*2+1].sm+=(a[p*2+1].r-a[p*2+1].l+1)*a[p].add;
		a[p].add=0;
	}
}
void Build(int p,int l,int r){
	a[p].l=l,a[p].r=r;
	if(l==r){
		a[p].sm=wt[l];
		return ;
	}
	int mid=(l+r)/2;
	Build(p*2,l,mid);
	Build(p*2+1,mid+1,r);
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ;
}
void add(int p,int l,int r,int x){
	if(a[p].l>=l&&a[p].r<=r){
		a[p].sm+=(a[p].r-a[p].l+1)*x;
		a[p].add+=x;
		return ;
	}
	Spread(p);
	int mid=(a[p].l+a[p].r)/2;
	if(l<=mid){
		add(p*2,l,r,x);
	}
	if(r>mid){
		add(p*2+1,l,r,x);
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ;
}
int ask(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		return a[p].sm;
	}
	Spread(p);
	int mid=(a[p].l+a[p].r)/2,ans=0;
	if(l<=mid){
		ans+=ask(p*2,l,r);
	}
	if(r>mid){
		ans+=ask(p*2+1,l,r);
	}
	return ans;
}
int QRd(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		ans+=ask(1,id[top[x]],id[x]);
		ans%=mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	ans+=ask(1,id[x],id[y]);
	return ans%mod;
}
void UpdateRd(int x,int y,int k){
	k%=mod;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		add(1,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	add(1,id[x],id[y],k);
}
void dfs1(int u,int faa){
	fa[u]=faa;
	size[u]=1;
	dep[u]=dep[faa]+1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==faa){
			continue; 
		}
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	id[u]=++cnt;
	wt[cnt]=w[u];
	top[u]=tp;
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
signed main(){
	ios::sync_with_stdio(0);
    cin>>n>>m>>root>>mod;
    for(int i=1;i<=n;i++){
		cin>>w[i];
	}
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        add(a,b);
		add(b,a);
    }
    dfs1(root,0);
    dfs2(root,root);
    Build(1,1,n);
	while(m--){
        int k,x,y,z;
        cin>>k;
        if(k==1){
            cin>>x>>y>>z;
            UpdateRd(x,y,z);
        }
        else if(k==2){
            cin>>x>>y;
            printf("%d\n",QRd(x,y)%mod);
        }
        else if(k==3){
            cin>>x>>y;
            add(1,id[x],id[x]+size[x]-1,y);
        }
        else{
            cin>>x;
            printf("%d\n",ask(1,id[x],id[x]+size[x]-1)%mod);
    	}
    }
}
/*
如题，已知一棵包含 N 个结点的树（连通且无环），每个节点上包含一个数值，需要支持以下操作：

1 x y z，表示将树从 x 到 y 结点最短路径上所有节点的值都加上 z。

2 x y，表示求树从 x 到 y 结点最短路径上所有节点的值之和。

3 x z，表示将以 x 为根节点的子树内所有节点值都加上 z。

4 x，表示求以 x 为根节点的子树内所有节点值之和。
*/
