#include <bits/stdc++.h>
using namespace std;
struct Splay{
	int ch[3],fa,val,sm,rev;
}a[1000010];
int n,m;
bool isroot(int x){
	if(a[a[x].fa].ch[0]==x||a[a[x].fa].ch[1]==x){
		return 0;
	}
	return 1;
}
void pushdown(int p){
	if(a[p].rev){
		swap(a[p].ch[0],a[p].ch[1]);
		a[a[p].ch[0]].rev^=1;
		a[a[p].ch[1]].rev^=1;
		a[p].rev=0;
	}
	return ;
}
void pushup(int p){
	a[p].sm=a[p].val^a[a[p].ch[0]].sm^a[a[p].ch[1]].sm;
}
void push(int p){
	if(!isroot(p)){
		push(a[p].fa);
	}
	pushdown(p);
}
void rotate(int x){
	int y=a[x].fa;
	int z=a[y].fa;
	int kid=a[y].ch[1]==x;
	if(!isroot(y)){
		a[z].ch[a[z].ch[1]==y]=x;
	}
	a[x].fa=z;
	a[y].ch[kid]=a[x].ch[kid^1];
	a[a[x].ch[kid^1]].fa=y;
	a[x].ch[kid^1]=y;
	a[y].fa=x;
	pushup(y);
	pushup(x);
	return ;
}
void splay(int x){
	push(x);
	while(!isroot(x)){
		int y=a[x].fa;
		int z=a[y].fa;
		if(!isroot(y)){
			(a[z].ch[1]==y)^(a[y].ch[1]==x)?rotate(x):rotate(y);
		}
		rotate(x);
	}
	return ;
}
void access(int x){
	int y=0;
	while(x){
		splay(x);
		a[x].ch[1]=y;
		pushup(x);
		y=x,x=a[x].fa;
	}
	return ;
}
void makeroot(int x){
	access(x);
	splay(x);
	a[x].rev^=1;
	return ;
}
void split(int x,int y){
	makeroot(x);
	access(y);
	splay(y);
	return ;
}
int ask(int x,int y){
	split(x,y);
	return a[y].sm;
}
int findroot(int x){
	access(x);
	splay(x);
	while(a[x].ch[0]){
		pushdown(x);
		x=a[x].ch[0];
	}
	splay(x);
	return x;
}
void link(int x,int y){
	makeroot(x);
	if(findroot(y)==x){
		return ;
	}
	a[x].fa=y;
	return ;
}
void cut(int x,int y){
	makeroot(x);
	if(findroot(y)==x&&a[y].fa==x&&(!a[y].ch[0])){
		a[y].fa=0;
		pushup(x);
	}
	return ;
}
void change(int x,int y){
	splay(x);
	a[x].val=y;
	pushup(x);
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
	}
	for(int i=1;i<=m;i++){
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==0){
			cout<<ask(x,y)<<endl;
		}
		if(opt==1){
			link(x,y);
		}
		if(opt==2){
			cut(x,y);
		}
		if(opt==3){
			change(x,y);
		}
	}
}
/*
给定 n 个点以及每个点的权值，要你处理接下来的 m 个操作。
操作有四种，操作从 0 到 3 编号。点从 1 到 n 编号。
 
0 x y 代表询问从 x 到 y 的路径上的点的权值的 xor 和。保证 x 到 y 是联通的。
1 x y 代表连接 x 到 y，若 x 到 y 已经联通则无需连接。
2 x y 代表删除边 (x,y)，不保证边 (x,y) 存在。
3 x y 代表将点 x 上的权值变成 y。

*/
