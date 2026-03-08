#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9;
int n,m,vv[1000010],root,cnt,id[1000010];
struct splay{
	int ch[3],fa,size,sm,rev,cov,mxl,mxr,mx,val;
}a[1000010];
queue<int> q;
void pushup(int x){
	a[x].size=a[a[x].ch[0]].size+a[a[x].ch[1]].size+1;
	a[x].sm=a[a[x].ch[0]].sm+a[a[x].ch[1]].sm+a[x].val;
	a[x].mx=max(max(a[a[x].ch[0]].mx,a[a[x].ch[1]].mx),
			a[a[x].ch[0]].mxr+a[a[x].ch[1]].mxl+a[x].val);
	a[x].mxl=max(a[a[x].ch[0]].mxl,a[a[x].ch[0]].sm+a[x].val+a[a[x].ch[1]].mxl);
	a[x].mxr=max(a[a[x].ch[1]].mxr,a[a[x].ch[1]].sm+a[x].val+a[a[x].ch[0]].mxr);
	return ;
}
void pushdown(int x){
	if(a[x].cov){
		a[x].rev=a[x].cov=0;
		if(a[x].ch[0]){
			a[a[x].ch[0]].cov=1;
			a[a[x].ch[0]].val=a[x].val;
			a[a[x].ch[0]].sm=a[x].val*a[a[x].ch[0]].size;
		}
		if(a[x].ch[1]){
			a[a[x].ch[1]].cov=1;
			a[a[x].ch[1]].val=a[x].val;
			a[a[x].ch[1]].sm=a[x].val*a[a[x].ch[1]].size;
		}
		if(a[x].val>=0){
			if(a[x].ch[0]){
				a[a[x].ch[0]].mxl=a[a[x].ch[0]].mxr=a[a[x].ch[0]].sm; 
				a[a[x].ch[0]].mx=a[a[x].ch[0]].sm;
			}
			if(a[x].ch[1]){
				a[a[x].ch[1]].mxl=a[a[x].ch[1]].mxr=a[a[x].ch[1]].sm;
				a[a[x].ch[1]].mx=a[a[x].ch[1]].sm;
			}
		}
		else{
			if(a[x].ch[0]){
				a[a[x].ch[0]].mxl=a[a[x].ch[0]].mxr=0;
				a[a[x].ch[0]].mx=a[x].val;
			}
			if(a[x].ch[1]){
				a[a[x].ch[1]].mxl=a[a[x].ch[1]].mxr=0;
				a[a[x].ch[1]].mx=a[x].val;
			}
		}
	}
	if(a[x].rev){
		a[x].rev=0;
		a[a[x].ch[0]].rev^=1;
		a[a[x].ch[1]].rev^=1;
		swap(a[a[x].ch[0]].mxl,a[a[x].ch[0]].mxr);
		swap(a[a[x].ch[1]].mxl,a[a[x].ch[1]].mxr);
		swap(a[a[x].ch[0]].ch[0],a[a[x].ch[0]].ch[1]);
		swap(a[a[x].ch[1]].ch[0],a[a[x].ch[1]].ch[1]);
	}
}
void Rotate(int x){
	int y=a[x].fa;
	int z=a[y].fa;
	int kid=a[y].ch[1]==x;
	a[z].ch[a[z].ch[1]==y]=x;
	a[x].fa=z;
	a[y].ch[kid]=a[x].ch[kid^1];
	a[a[x].ch[kid^1]].fa=y;
	a[x].ch[kid^1]=y;
	a[y].fa=x;
	pushup(y);
	pushup(x);
	return ;
}
void Splay(int x,int goal){
	while(a[x].fa!=goal){
		int y=a[x].fa;
		int z=a[y].fa;
		if(z!=goal){
			(a[z].ch[1]==y)^(a[y].ch[1]==x)?Rotate(x):Rotate(y);
		}
		Rotate(x);
	}
	if(goal==0){
		root=x;
	}
	return ;
}
int Find(int x,int rank){
	pushdown(x);
	if(a[a[x].ch[0]].size>=rank){
		return Find(a[x].ch[0],rank);
	}
	if(a[a[x].ch[0]].size+1==rank){
		return x;
	}
	return Find(a[x].ch[1],rank-a[a[x].ch[0]].size-1);
}
void Build(int fa,int l,int r){
	int mid=(l+r)/2,now=id[mid],faa=id[fa];
	if(l==r){
		a[now].mx=a[now].sm=vv[l];
		a[now].cov=a[now].rev=0;
		a[now].mxl=a[now].mxr=max(vv[l],0ll);
		a[now].size=1;
	}
	if(l<mid){
		Build(mid,l,mid-1);
	}
	if(r>mid){
		Build(mid,mid+1,r);
	}
	a[now].val=vv[mid];
	a[now].fa=faa;
	pushup(now);
	a[faa].ch[mid>=fa]=now;
	return ;
}
void Insert_Build(int pos,int tot){
	for(int i=1;i<=tot;i++){
		cin>>vv[i];
	}
	for(int i=1;i<=tot;i++){
		if(!q.empty()){
			id[i]=q.front();
			q.pop();
			continue;
		}
		id[i]=++cnt;
	}
	Build(0,1,tot);
	int loc=id[(tot+1)>>1];
	int pre=Find(root,pos+1);
	int nxt=Find(root,pos+2);
	Splay(pre,0);
	Splay(nxt,root);
	a[loc].fa=nxt;
	a[nxt].ch[0]=loc;
	pushup(nxt);
	pushup(pre);
	return ;
}
void Recycle(int x){
    if(a[x].ch[0]){
    	Recycle(a[x].ch[0]);
	}
    if(a[x].ch[1]){
    	Recycle(a[x].ch[1]);
	}
    q.push(x);
    a[x].fa=a[x].ch[0]=a[x].ch[1]=a[x].cov=a[x].rev=0;
}
void Delete(int pos,int tot){
	int pre=Find(root,pos);
	int nxt=Find(root,pos+tot+1);
	Splay(pre,0);
	Splay(nxt,root);
	Recycle(a[nxt].ch[0]);
	a[nxt].ch[0]=0;
	pushup(nxt);
	pushup(pre);
	return ;
}
void Cover(int pos,int tot,int c){
	int pre=Find(root,pos);
	int nxt=Find(root,pos+tot+1);
	Splay(pre,0);
	Splay(nxt,root);
	int now=a[nxt].ch[0];
	a[now].val=c;
	a[now].cov=1;
	a[now].sm=a[now].size*c;
	if(c>=0){
		a[now].mxl=a[now].mxr=a[now].mx=a[now].sm;
	}
	else{
		a[now].mxl=a[now].mxr=0;
		a[now].mx=c;
	}
	pushup(nxt);
	pushup(pre);
	return ;
}
void Flip(int pos,int tot){
	int pre=Find(root,pos);
	int nxt=Find(root,pos+tot+1);
	Splay(pre,0);
	Splay(nxt,root);
	int now=a[nxt].ch[0];
	a[now].rev^=1;
	swap(a[now].ch[0],a[now].ch[1]);
    swap(a[now].mxl,a[now].mxr);
	pushup(nxt);
	pushup(pre);
	return ;
}
int AskSum(int pos,int tot){
	int pre=Find(root,pos);
	int nxt=Find(root,pos+tot+1);
	Splay(pre,0);
	Splay(nxt,root);
	int now=a[nxt].ch[0];
	return a[now].sm;
}
int AskMaxSum(){
	return a[root].mx;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	a[0].mx=vv[1]=vv[n+2]=-inf; 
	for(int i=1;i<=n;i++){
		cin>>vv[i+1];
	}
	for(int i=1;i<=n+2;i++){
		id[i]=i;
	}
	Build(0,1,n+2);
	root=(n+3)/2;
	cnt=n+2;
	for(int i=1;i<=m;i++){
		string opt;
		int pos,tot;
		cin>>opt;
		if(opt=="INSERT"){
			cin>>pos>>tot;
			Insert_Build(pos,tot);
		}
		if(opt=="DELETE"){
			cin>>pos>>tot;
			Delete(pos,tot);
		}
		if(opt=="MAKE-SAME"){
			int c;
			cin>>pos>>tot>>c;
			Cover(pos,tot,c);
		}
		if(opt=="REVERSE"){
			cin>>pos>>tot;
			Flip(pos,tot);
		}
		if(opt=="GET-SUM"){
			cin>>pos>>tot;
			cout<<AskSum(pos,tot)<<endl;
		}
		if(opt=="MAX-SUM"){
			cout<<AskMaxSum()<<endl;
		}
	}
	return 0;
}
/*
1	插入	INSERT posi tot c1c2...ctot
在当前数列的第 posi 个数字后插入 tot 个数字：c1,c 2...ctot
若在数列首插入，则 posi 为 0
2	删除	DELETE posi tot
从当前数列的第 posi 个数字开始连续删除 tot 个数字
3	修改	MAKE-SAME posi tot c
从当前数列的第 posi个数字开始的连续 tot个数字统一修改为 c
4	翻转	REVERSE posi tot
取出从当前数列的第 posi 个数字开始的 tot 个数字，翻转后放入原来的位置
5	求和	GET-SUM posi tot
计算从当前数列的第 posi 个数字开始的 tot 个数字的和并输出
6	求最大子列和	MAX-SUM	
求出当前数列中和最大的一段非空子列，并输出最大和

*/
