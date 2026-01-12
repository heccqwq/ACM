#include<iostream>
#include<cstdio>
#include<algorithm> 
using namespace std;
const int inf=1e9;
int root,tot,n,tt,a[1000005];
struct Splay{
	int fa,ch[5],val,tag,size;
}t[1000005];
void maintain(int x) {t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+1;}
void pushdown(int x){
	if(x&&t[x].tag){
		t[t[x].ch[0]].tag^=1;
		t[t[x].ch[1]].tag^=1;
		swap(t[x].ch[0],t[x].ch[1]);
		t[x].tag=0;
	}
}
int build_tree(int x,int l,int r){
	if(l>r) return 0;
	int mid=(l+r)>>1;
	int now=++tot;
	t[now].ch[0]=t[now].ch[1]=0;
	t[now].val=a[mid];
	t[now].fa=x;
	t[now].tag=0;
	t[now].ch[0]=build_tree(now,l,mid-1);
	t[now].ch[1]=build_tree(now,mid+1,r); 
	maintain(now);
	return now;
} 

bool get(int x) {return x==t[t[x].fa].ch[1]; }
void rotate(int x){
	//cout<<1;
	int y=t[x].fa;
	int z=t[y].fa;
	int kid=t[y].ch[1]==x;
	pushdown(y);
	pushdown(x);
	t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[kid]=t[x].ch[kid^1];
	t[t[x].ch[kid^1]].fa=y;
	t[x].ch[kid^1]=y;
	t[y].fa=x;
	maintain(y);
	maintain(x);
}//旋转第二步 
void splay(int x,int goal){
	while(t[x].fa!=goal){
		//cout<<1;
		int y=t[x].fa,z=t[y].fa;
		if(z!=goal)
		(get(y)^get(x))?rotate(x):rotate(y);
		rotate(x);
	}
	if(goal==0) root=x;
}
int kth(int p,int rank){
	if(!p){
		return 0;
	}
	if(t[t[p].ch[0]].size>=rank){
		return kth(t[p].ch[0],rank);
	}
	if(t[t[p].ch[0]].size+1>=rank){
		return p;
	}
	return kth(t[p].ch[1],rank-t[t[p].ch[0]].size-1);
	
}
void flip(int l,int r){
	int ll=kth(root,l-1);
	int rr=kth(root,r+1);
	splay(ll,0);
	splay(rr,ll);
	t[t[t[root].ch[1]].ch[0]].tag^=1;
}
void write(int x){
	pushdown(x);
	if(t[x].ch[0]) write(t[x].ch[0]);
	if(t[x].val!=inf&&t[x].val!=-inf) cout<<t[x].val<<" ";
	if(t[x].ch[1]) write(t[x].ch[1]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>tt;
	a[1]=-inf,a[n+2]=inf;
	for(int i=1;i<=n;i++) a[i+1]=i; 
	root=build_tree(0,1,n+2); 
	for(int i=1;i<=tt;i++){
		int l,r;
		cin>>l>>r;
		flip(l+1,r+1);	
	}
	write(root);
	return 0;
}
/*
您需要写一种数据结构（可参考题目标题），来维护一个有序数列。

其中需要提供以下操作：翻转一个区间，例如原有序序列是 5 4 3 2 1，翻转区间是 [2,4] 的话，结果是 5 2 3 4 1。
*/
