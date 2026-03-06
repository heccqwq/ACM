#include <bits/stdc++.h>
#define int long long
using namespace std;
const int md=51061;
struct Splay{
	int ch[3],fa,val,sm,rev,add,tim,siz;
}a[1000010];
int n,m;
bool isroot(int x){
	if(a[a[x].fa].ch[0]==x||a[a[x].fa].ch[1]==x){
		return 0;
	}
	return 1;
}
void pushdown(int p){
    if(!p){
    	return;	
	}
    if(a[p].rev){
        swap(a[p].ch[0],a[p].ch[1]);
        if(a[p].ch[0]){
        	a[a[p].ch[0]].rev^=1;
		}
        if(a[p].ch[1]){
        	a[a[p].ch[1]].rev^=1;
		}
        a[p].rev=0;
    }
    if(a[p].tim!=1){
        int t=a[p].tim;
        if(a[p].ch[0]){
            a[a[p].ch[0]].val=(a[a[p].ch[0]].val*t)%md;
            a[a[p].ch[0]].sm=(a[a[p].ch[0]].sm*t)%md;
            a[a[p].ch[0]].add=(a[a[p].ch[0]].add*t)%md;
            a[a[p].ch[0]].tim=(a[a[p].ch[0]].tim*t)%md;
        }
        if(a[p].ch[1]){
            a[a[p].ch[1]].val=(a[a[p].ch[1]].val*t)%md;
            a[a[p].ch[1]].sm=(a[a[p].ch[1]].sm*t)%md;
            a[a[p].ch[1]].add=(a[a[p].ch[1]].add*t)%md;
            a[a[p].ch[1]].tim=(a[a[p].ch[1]].tim*t)%md;
        }
        a[p].tim=1;
    }
    if(a[p].add){
        if(a[p].ch[0]){
            a[a[p].ch[0]].val=(a[a[p].ch[0]].val+a[p].add)%md;
            a[a[p].ch[0]].sm=(a[a[p].ch[0]].sm+a[p].add*a[a[p].ch[0]].siz)%md;
            a[a[p].ch[0]].add=(a[a[p].ch[0]].add+a[p].add)%md;
        }
        if(a[p].ch[1]){
            a[a[p].ch[1]].val=(a[a[p].ch[1]].val+a[p].add)%md;
            a[a[p].ch[1]].sm=(a[a[p].ch[1]].sm+a[p].add*a[a[p].ch[1]].siz)%md;
            a[a[p].ch[1]].add=(a[a[p].ch[1]].add+a[p].add)%md;
        }
        a[p].add=0;
    }
}
void pushup(int p){
	if(!p){
		return ;
	}
	a[p].siz=1+a[a[p].ch[0]].siz+a[a[p].ch[1]].siz;
	a[p].sm=a[p].val+a[a[p].ch[0]].sm+a[a[p].ch[1]].sm;
	a[p].sm%=md;
	return ;
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
void add(int x,int y,int v){
	split(x,y);
	a[y].add+=v;
	a[y].val+=v;
	a[y].sm+=v*a[y].siz;
	a[y].sm%=md;
	return ;
}
void tim(int x,int y,int v){
	split(x,y);
	a[y].add*=v;
	a[y].val*=v;
	a[y].tim*=v;
	a[y].sm*=v;
	a[y].sm%=md;
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i].sm=a[i].val=a[i].tim=a[i].siz=1;
	}
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		link(a,b);
	}
	for(int i=1;i<=m;i++){
		int a,b,c,d;
		char opt;
		cin>>opt;
		if(opt=='+'){
			cin>>a>>b>>c;
			add(a,b,c);
		}
		if(opt=='-'){
			cin>>a>>b>>c>>d;
			cut(a,b);
			link(c,d);
		}
		if(opt=='*'){
			cin>>a>>b>>c;
			tim(a,b,c);
		}
		if(opt=='/'){
			cin>>a>>b;
			cout<<ask(a,b)<<endl;
		}
	}
}
/*
+ u v c:将u到v路径上的点权加上c
- u1 v1 u2 v2：将树中原有的边 (u1,v1) 删除，加入一条新边 (u2,v 2)，
保证操作完之后仍然是一棵树；
* u v c：将 u 到 v 的路径上的点的权值都乘上自然数 c；
/ u v：询问 u 到 v 的路径上的点的权值和，将答案对 51061 取模。

*/
