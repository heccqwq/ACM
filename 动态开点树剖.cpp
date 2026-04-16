#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,w[1000010],c[1000010],son[1000010],hed[1000010],siz[1000010];
int top[1000010],root[1000010],ver[1000010],nxt[1000010];
int fa[1000010],dep[1000010],id[1000010],sm,cnt,tot;
struct SegmentTree{
	int lc,rc,sum,fl,mx;
}a[100010<<4];
void add(int u,int v){
	ver[++tot]=v,nxt[tot]=hed[u],hed[u]=tot;
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
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	id[u]=++sm;
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
void Update(int x){
	a[x].sum=a[a[x].lc].sum+a[a[x].rc].sum;
	a[x].mx=max(a[a[x].lc].mx,a[a[x].rc].mx);
}
void Add(int p,int l,int r,int &x,int k){
	if(!x){
		x=++cnt;
	}
	a[x].mx=max(a[x].mx,k);
	a[x].sum+=k;
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	if(p<=mid){
		Add(p,l,mid,a[x].lc,k);
	}
	if(p>mid){
		Add(p,mid+1,r,a[x].rc,k);
	}
	return ;
}
void Cover0(int p,int l,int r,int &x){
	if(l==r){
		a[x].sum=a[x].mx=0;
		return;
	}
	int mid=(l+r)/2;
	if(p<=mid){
		Cover0(p,l,mid,a[x].lc);
	}
	if(p>mid){
		Cover0(p,mid+1,r,a[x].rc);
	}
	Update(x);
	return ;
}
int AskSum(int u,int v,int l,int r,int x){
	if(l>=u&&r<=v){
		return a[x].sum;
	}
	int mid=(l+r)/2,res=0;
	if(u<=mid){
		res+=AskSum(u,v,l,mid,a[x].lc);
	}
	if(v>mid){
		res+=AskSum(u,v,mid+1,r,a[x].rc);
	}
	return res; 
}
int AskRdSum(int x,int y,int k){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			ans+=AskSum(id[top[x]],id[x],1,n,root[k]);
			x=fa[top[x]];
			continue;
		}
		ans+=AskSum(id[top[y]],id[y],1,n,root[k]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	ans+=AskSum(id[x],id[y],1,n,root[k]);
	return ans;
}
int AskMax(int u,int v,int l,int r,int x){
	if(l>=u&&r<=v){
		return a[x].mx;
	}
	int mid=(l+r)/2,ans=0;
	if(u<=mid){
		ans=max(ans,AskMax(u,v,l,mid,a[x].lc));
	}
	if(v>mid){
		ans=max(ans,AskMax(u,v,mid+1,r,a[x].rc));
	}
	return ans;
}
int AskRdMax(int x,int y,int k){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			ans=max(ans,AskMax(id[top[x]],id[x],1,n,root[k]));
			x=fa[top[x]];
			continue;
		}
		ans=max(ans,AskMax(id[top[y]],id[y],1,n,root[k]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	ans=max(ans,AskMax(id[x],id[y],1,n,root[k]));
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>c[i];
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++){
		Add(id[i],1,n,root[c[i]],w[i]);
	}
	for(int i=1,x,y;i<=q;i++){
		char opt[4];
		cin>>opt>>x>>y;
		if(opt[1]=='C'){
			Cover0(id[x],1,n,root[c[x]]);
			Add(id[x],1,n,root[y],w[x]);
			c[x]=y;
		}
		if(opt[1]=='W'){
			Cover0(id[x],1,n,root[c[x]]);
			Add(id[x],1,n,root[c[x]],y);
			w[x]=y;
		}
		if(opt[1]=='S'){
			cout<<AskRdSum(x,y,c[x])<<endl;
		}
		if(opt[1]=='M'){
			cout<<AskRdMax(x,y,c[x])<<endl;
		}
	}
	return 0;
}
/*
S 国有 N 个城市，编号从 1 到 N。
城市间用 N-1条双向道路连接，满足一个城市出发可达所有城市。每个城市信仰不同的宗教。
为了方便，我们用不同的正整数代表各种宗教，S 国的居民常常旅行。
旅行时他们总会走最短路，并且为了避免麻烦，只在信仰和他们相同的城市留宿。
当然旅程的终点也是信仰与他相同的城市。S 国为每个城市标定了不同的旅行评级，
旅行者们常会记下途中（包括起点和终点）留宿过的城市的评级总和或最大值。
在 S 国的历史上常会发生以下几种事件：
CC x c：城市 x 的居民全体改信了 c 教；
CW x w：城市 x 的评级调整为 w；
QS x y：一位旅行者从城市 x 出发，到城市 y，并记下了途中留宿过的城市的评级总和；
QM x y：一位旅行者从城市 x 出发，到城市 y，并记下了途中留宿过的城市的评级最大值。
由于年代久远，旅行者记下的数字已经遗失了，但记录开始之前每座城市的信仰与评级，
还有事件记录本身是完好的。请根据这些信息，还原旅行者记下的数字。
为了方便，我们认为事件之间的间隔足够长，以致在任意一次旅行中，
所有城市的评级和信仰保持不变。

输入格式
输入的第一行包含整数 N,Q 依次表示城市数和事件数。
接下来 N 行，第 i+1 行两个整数 Wi,Ci依次表示记录开始之前，城市 i 的评级和信仰。
接下来 N-1 行每行两个整数 x,y 表示一条双向道路。
接下来 Q 行，每行一个操作，格式如上所述。

输出格式
对每个 QS 和 QM 事件，输出一行，表示旅行者记下的数字。
*/
