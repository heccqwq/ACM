#include <bits/stdc++.h>
using namespace std;
const int inf=2147483647;
int n,m,w[500050],tot;
struct Splay{
	int ch[2],fa,val,cnt,size;
}t[10000050];
struct SegmentTree{
	int l,r,root;
}st[4000050];
int newnode(int val,int fa){
	++tot;
	t[tot].ch[0]=t[tot].ch[1]=0;
	t[tot].fa=fa;
	t[tot].val=val;
	t[tot].cnt=t[tot].size=1;
	return tot;
}
void Update(int p){
	t[p].size=t[t[p].ch[0]].size+t[t[p].ch[1]].size+t[p].cnt;
}
void Rotate(int x){
	int y=t[x].fa;
	int z=t[y].fa;
	int kid=t[y].ch[1]==x;
	t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[kid]=t[x].ch[kid^1];
	t[t[x].ch[kid^1]].fa=y;
	t[x].ch[kid^1]=y;
	t[y].fa=x;
	Update(y);
	Update(x);
}
void Splay(int &root,int x,int goal){
	while(t[x].fa!=goal){
		int y=t[x].fa;
		int z=t[y].fa;
		if(z!=goal){
			(t[z].ch[1]==y)^(t[y].ch[1]==x)?Rotate(x):Rotate(y);
		}
		Rotate(x);
	}
	if(goal==0){
		root=x;
	}
}
void Insert(int &root,int val){
	int now=root,fa=0;
	while(now&&t[now].val!=val){
		fa=now;
		now=t[now].ch[t[now].val<val];
	}
	if(now){
		t[now].cnt++;
		Update(now);
		Splay(root,now,0);
		return;
	}
	now=newnode(val,fa);
	if(fa){
		t[fa].ch[t[fa].val<val]=now;
	}
	Splay(root,now,0);
}
void Search(int &root,int val){
	int now=root,last=0;
	while(now&&t[now].val!=val){
		last=now;
		now=t[now].ch[t[now].val<val];
	}
	if(now){
		Splay(root,now,0);
	}
	else if(last){
		Splay(root,last,0);
	}
}
int GetRank(int &root,int val){
	int now=root,ans=0,last=0;
	while(now){
		last=now;
		if(t[now].val<val){
			ans+=t[t[now].ch[0]].size+t[now].cnt;
			now=t[now].ch[1];
			continue;
		}
		now=t[now].ch[0];
	}/*
	if(last){
		Splay(root,last,0);
	}*/
	return ans;
}
int GetPre(int &root,int val){
	Search(root,val);
	if(t[root].val<val){
		return root;
	}
	int now=t[root].ch[0];
	while(t[now].ch[1]){
		now=t[now].ch[1];
	}
	return now;
}
int GetNext(int &root,int val){
	Search(root,val);
	if(t[root].val>val){
		return root;
	}
	int now=t[root].ch[1];
	while(t[now].ch[0]){
		now=t[now].ch[0];
	}
	return now;
}
void Remove(int &root,int val){
	int pre=GetPre(root,val);
	int nxt=GetNext(root,val);
	Splay(root,pre,0);
	Splay(root,nxt,pre);
	int now=t[nxt].ch[0];
	if(!now){
		return ;
	}
	if(t[now].cnt>1){
		t[now].cnt--;
		Update(now);
		Update(nxt);
		Update(pre);
		return ;
	}
	t[nxt].ch[0]=0;
	Update(nxt);
	Update(pre);
}
void Build(int p,int l,int r){
	st[p].l=l,st[p].r=r,st[p].root=0;
	Insert(st[p].root,-inf);
	Insert(st[p].root,inf);
	for(int i=l;i<=r;i++){
		Insert(st[p].root,w[i]);
	}
	if(l==r){
		return ;
	}
	int mid=(l+r)/2;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
}
void Change(int p,int pos,int oldval,int newval){
	Remove(st[p].root,oldval);
	Insert(st[p].root,newval);
	if(st[p].l==st[p].r){
		return ;
	}
	int mid=(st[p].l+st[p].r)/2;
	if(pos<=mid){
		Change(p<<1,pos,oldval,newval);
		return ;
	}
	Change(p<<1|1,pos,oldval,newval);
}
int QueryRank(int p,int l,int r,int k){
	if(st[p].l>=l&&st[p].r<=r){
		return GetRank(st[p].root,k)-1;
	}
	int mid=(st[p].l+st[p].r)/2,ans=0;
	if(l<=mid){
		ans+=QueryRank(p<<1,l,r,k);
	}
	if(r>mid){
		ans+=QueryRank(p<<1|1,l,r,k);
	}
	return ans;
}
int QueryKth(int l,int r,int k){
	int L=0,R=100000000,ans=0;
	while(L<=R){
		int mid=(L+R)/2;
		int rk=QueryRank(1,l,r,mid)+1;
		if(rk<=k){
			ans=mid;
			L=mid+1;
		}
		else{
			R=mid-1;
		}
	}
	return ans;
}
int QueryPre(int p,int l,int r,int k){
	if(st[p].l>=l&&st[p].r<=r){
		return t[GetPre(st[p].root,k)].val;
	}
	int mid=(st[p].l+st[p].r)/2,ans=-inf;
	if(l<=mid){
		ans=max(ans,QueryPre(p<<1,l,r,k));
	}
	if(r>mid){
		ans=max(ans,QueryPre(p<<1|1,l,r,k));
	}
	return ans;
}
int QueryNext(int p,int l,int r,int k){
	if(st[p].l>=l&&st[p].r<=r){
		return t[GetNext(st[p].root,k)].val;
	}
	int mid=(st[p].l+st[p].r)/2,ans=inf;
	if(l<=mid){
		ans=min(ans,QueryNext(p*2,l,r,k));
	}
	if(r>mid){
		ans=min(ans,QueryNext(p*2+1,l,r,k));
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	Build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt,l,r,k;
		cin>>opt;
		if(opt==1){
			cin>>l>>r>>k;
			cout<<QueryRank(1,l,r,k)+1<<endl;
		}
		if(opt==2){
			cin>>l>>r>>k;
			cout<<QueryKth(l,r,k)<<endl;
		}
		if(opt==3){
			cin>>l>>k;
			Change(1,l,w[l],k);
			w[l]=k;
		}
		if(opt==4){
			cin>>l>>r>>k;
			int ans=QueryPre(1,l,r,k);
			if(ans==inf){
				cout<<2147483647<<endl;
				continue;
			}
			cout<<ans<<endl;
		}
		if(opt==5){
			cin>>l>>r>>k;
			int ans=QueryNext(1,l,r,k);
			if(ans==inf){
				cout<<2147483647<<endl;
				continue;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
/*
您需要写一种数据结构，来维护一个有序数列，其中需要提供以下操作：
1查询 k 在区间内的排名；
2查询区间内排名为 k 的值；
3修改某一位置上的数值；
4查询 k 在区间内的前驱（前驱定义为严格小于 x，且最大的数，若不存在输出 -2147483647）
5查询 k 在区间内的后继（后继定义为严格大于 x，且最小的数，若不存在输出 2147483647）
1≤n,m≤2e5
序列中的值在任何时刻 ∈[0,1e8]
*/
