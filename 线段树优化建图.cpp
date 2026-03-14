#include<bits/stdc++.h>
#define int long long
using namespace std;
const int md=1e9+7;
struct SegmentTree{
	int l,r,id;
}a[2000010];
int n,k,cnt,smscc,ans,tot,dfn[2000005],lmn[2000005],rmx[2000005],low[2000005];
int blg[2000005],hed[2000005],inedg[2000005],sz[2000005],ver[20000005];
int nxt[20000005],hedd[2000005],nxtt[20000005],verr[20000005];
int x[500005],r[500005],id[2000005];
queue<int> q;
stack<int> s;
void add(int u,int v){
	ver[++tot]=v,nxt[tot]=hed[u],hed[u]=tot;
}
void addd(int u,int v){
	verr[++tot]=v,nxtt[tot]=hedd[u],hedd[u]=tot;
}
void build(int p,int l,int r){
	a[p].l=l,a[p].r=r;
	if(l==r){
		id[l]=p;
		k=max(k,p);
		return ;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	add(p,p*2);
	add(p,p*2+1);
	return ;
}
void add(int p,int tl,int tr,int id){
	if(tl<=a[p].l&&a[p].r<=tr){
		if(id!=p){
			add(id,p);
		}
		return ;
	}
	int mid=(a[p].l+a[p].r)/2;
	if(mid>=tl){
		add(p*2,tl,tr,id);
	}
	if(mid<tr){
		add(p*2+1,tl,tr,id);
	}
}
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!blg[v]){
			low[u]=min(low[u],low[v]);
		}
	}
	if(dfn[u]==low[u]){
		int v;
		smscc++;
		do{
			v=s.top();
			s.pop();
			blg[v]=smscc;
			lmn[smscc]=min(lmn[smscc],a[v].l);
			rmx[smscc]=max(rmx[smscc],a[v].r);
		}while(u!=v);
	}
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>r[i];
	}
	memset(lmn,0x3f,sizeof lmn);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int ll=lower_bound(x+1,x+1+n,x[i]-r[i])-x;
		int rr=upper_bound(x+1,x+1+n,x[i]+r[i])-x-1;
		add(1,ll,rr,id[i]);
	}
	tarjan(1);
	cnt=0;
	for(int i=1;i<=k;i++){
		for(int j=hed[i];j;j=nxt[j]){
			if(blg[i]!=blg[ver[j]]){
				inedg[blg[i]]++;
				addd(blg[ver[j]],blg[i]);
			}
		}
	}
	for(int i=1;i<=smscc;i++){
		if(!inedg[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=hedd[u];i;i=nxtt[i]){
			int v=verr[i];
			lmn[v]=min(lmn[u],lmn[v]);
			rmx[v]=max(rmx[u],rmx[v]);
			inedg[v]--;
			if(!inedg[v]){
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=(ans+i*(rmx[blg[id[i]]]-lmn[blg[id[i]]]+1))%md;
	}
	cout<<ans;
	return 0;
}
/*
题目描述
在一条直线上有 n 个炸弹，每个炸弹的坐标是 xi，爆炸半径是 ri 
当一个炸弹爆炸时，如果另一个炸弹所在位置 xj满足 ∣xj-xi∣≤ri，
那么，该炸弹也会被引爆。现在，请你帮忙计算一下，先把第 i 个炸弹引爆，
将引爆多少个炸弹呢？

答案对 1e9+7取模。
输入格式
第一行，一个数字 n ，表示炸弹个数。
第 2?n+1 行，每行两个整数，表示 xi，ri，保证 xi严格递增。
输出格式
			   i=1
一个数字，表示 ∑i*炸弹 i 能引爆的炸弹个数。
			   n
*/
