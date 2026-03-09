#include <bits/stdc++.h>
using namespace std;
struct Splay{
	int ch[3],fa,val,sm,rev,cov;
}a[1000010];
struct Edg{
	int u,v,ext;
}edg[1000010];
struct Qus{
	int opt,u,v,id;
}q[1000010];
int n,m,cnt,ans[1000010],cntans;
bool isroot(int x){
	if(a[a[x].fa].ch[0]==x||a[a[x].fa].ch[1]==x){
		return 0;
	}
	return 1;
}
void pushdown(int p){
	if(a[p].cov){
		if(a[p].ch[0]){
			a[a[p].ch[0]].val=0;
			a[a[p].ch[0]].sm=0;
			a[a[p].ch[0]].cov=1;
		}
		if(a[p].ch[1]){
			a[a[p].ch[1]].val=0;
			a[a[p].ch[1]].sm=0;
			a[a[p].ch[1]].cov=1;
		}
		a[p].cov=0;
	}
	if(a[p].rev){
		swap(a[p].ch[0],a[p].ch[1]);
		a[a[p].ch[0]].rev^=1;
		a[a[p].ch[1]].rev^=1;
		a[p].rev=0;
	}
	return ;
}
void pushup(int p){
	a[p].sm=a[p].val+a[a[p].ch[0]].sm+a[a[p].ch[1]].sm;
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
void add(int x,int y,int eid){
	if(findroot(x)==findroot(y)){
        split(x,y);
        a[y].cov=1;
        pushdown(y);
    }
    else{
        a[eid].val=1;
        a[eid].sm=1;
        link(x,eid);
        link(eid,y);
    }
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>edg[i].u>>edg[i].v;
		if(edg[i].u>edg[i].v){
			swap(edg[i].u,edg[i].v);
		}
		edg[i].ext=1;
	}
	while(1){
		int opt;
		cin>>opt;
		if(opt==-1){
			break;
		}
		cnt++;
		q[cnt].opt=opt;
		cin>>q[cnt].u>>q[cnt].v;
		if(opt==0){
			if(q[cnt].u>q[cnt].v){
				swap(q[cnt].u,q[cnt].v);
			}
			for(int j=1;j<=m;j++){
				if(edg[j].u==q[cnt].u&&edg[j].v==q[cnt].v){
					q[cnt].id=j;
					edg[j].ext=0;
					break;
				}
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(edg[i].ext){
			int u=edg[i].u,v=edg[i].v;
			int eid=n+i;
			if(findroot(u)!=findroot(v)){
				a[eid].val=1;
				a[eid].sm=1;
				link(u,eid);
				link(eid,v);
			}
			else{
				split(u,v);
				a[v].cov=1;
				pushdown(v);
				a[eid].val=0;
				a[eid].sm=0;
				link(u,eid);
				link(eid,v);
			}
		}
	}
	for(int i=cnt;i>=1;i--){
		if(q[i].opt==0){
			int eid=n+q[i].id;
			add(q[i].u,q[i].v,eid);
		}
		else{
			ans[++cntans]=ask(q[i].u,q[i].v);
		}
	}
	for(int i=cntans;i>=1;i--){
		cout<<ans[i]<<endl;
	}
}
/*
A,B 两星球之间，如果某条航线不存在，
就无法从 A 星球抵达 B 星球，我们则称这条航线为关键航线。
若 op=1，则后接两个整数 u,v，表示询问当前 u,v 两星球之间有多少关键航线。
若 op=0，则后接两个整数 u,v，表示 u,v 之间的航线被破坏。
若 op=-1，则表示输入结束，后面不再存在操作。

逆序完成操作，因为只有加边操作，
所以实际上只有关键边变非关键边，而不存在非关键边变成关键边。
一条关键边对于任意两个过其的点都是关键边
对每个边维护一下其是否为关键边，如果是其边权为1，否则其边权为0 

在 LCT 中，通常节点代表树上的点。为了维护边的信息（比如这条边是不是桥），
代码采用了经典的技巧：每一条无向边 (u,v) 视为一个新的虚拟节点。
假设原图有n个点，第i条边对应的虚拟节点编号为n+i
在 LCT 中，原本连接 u和 v的边，变成了两条树边：u(n+i)和 v(n+i)。
边的属性（是否为关键航线）存储在这个虚拟节点 (n+i)的val字段中：
val = 1：表示该边是关键航线（桥）。
val = 0：表示该边不是关键航线（在某个环中）。

LCT 限制：只能维护点上的信息。
解决方案：把每一条边 (u,v) 变成一个新节点（即虚拟节点 eid = n + i），
然后把原来的边拆成两条边： u→eid和 eid→v 。

*/
