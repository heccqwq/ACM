#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,id,fa[1000010],del[1000010];
map<pair<int,int>,int> edg;
struct Edge{
    int u,v,w,id;
}edgg[1000010],temp[1000010];
struct Query{
    int k,u,v,ans;
}qs[1000010];
bool cmp(Edge a,Edge b){
    return a.w<b.w;
}
int Find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=Find(fa[x]);
}
struct Splay{
    int fa,ch[3],rev,mx,val;
}a[1000010];
bool isroot(int x){
    if(a[a[x].fa].ch[0]==x||a[a[x].fa].ch[1]==x){
        return 0;
    }
    return 1;
}
void pushup(int x){
	a[x].mx=x;
    if(a[x].ch[0]&&a[a[a[x].ch[0]].mx].val>a[a[x].mx].val){
        a[x].mx=a[a[x].ch[0]].mx;
    }
    if(a[x].ch[1]&&a[a[a[x].ch[1]].mx].val>a[a[x].mx].val){
        a[x].mx=a[a[x].ch[1]].mx;
    }
}
void pushdown(int x){
    if(a[x].rev){
        swap(a[x].ch[0],a[x].ch[1]);
        if(a[x].ch[0]){
        	a[a[x].ch[0]].rev^=1;
		}
        if(a[x].ch[1]){
        	a[a[x].ch[1]].rev^=1;
		}
        a[x].rev=0;
    }
    return ;
}
void push(int x){
    if(!isroot(x)){
        push(a[x].fa);
    }
    pushdown(x);
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
        if(!isroot(y)) {
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
int findroot(int x){
    access(x);
    splay(x);
    pushdown(x); 
    while(a[x].ch[0]){
        pushdown(x);
        x=a[x].ch[0];
    }
    splay(x);
    return x;
}
void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        a[x].fa=y;
    }
    return ;
}
void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&a[y].fa==x&&(!a[y].ch[0])){
    	a[x].ch[1]=0;
        a[y].fa=0;
        pushup(x);
    }
    return ;
}
int Que(int x,int y){
    split(x,y);
    return a[y].mx;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        a[i].val=0;
        a[i].mx=i;
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v,t;
        cin>>u>>v>>t;
        if(u>v){
        	swap(u,v);
		}
        edgg[i].u=u;
        edgg[i].v=v;
        edgg[i].w=t;
        edgg[i].id=i;
        edg[{u,v}]=i;
        a[n+i].val=t;
        a[n+i].mx=n+i;
    }
    for(int i=1;i<=q;i++){
        cin>>qs[i].k>>qs[i].u>>qs[i].v;
        if(qs[i].u>qs[i].v){
        	swap(qs[i].u,qs[i].v);
		}
        if(qs[i].k==2){
            int eid=edg[{qs[i].u,qs[i].v}];
            del[eid]=1;
        }
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(!del[i]){
            temp[++cnt]=edgg[i];
        }
    }
    sort(temp+1,temp+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        int fu=Find(temp[i].u);
        int fv=Find(temp[i].v);
        if(fu!=fv) {
            fa[fu]=fv;
            link(temp[i].u,n+temp[i].id);
            link(temp[i].v,n+temp[i].id);
        }
    }
    for(int i=q;i>=1;i--){
        if(qs[i].k==1){
            split(qs[i].u,qs[i].v);
            qs[i].ans=a[a[qs[i].v].mx].val;
        }
		else{
            int eid=edg[{qs[i].u,qs[i].v}];
            int u=qs[i].u,v=qs[i].v,w=edgg[eid].w;
            split(u,v);
            int mx_n=a[v].mx;
            if(a[mx_n].val>w){
                int id=mx_n-n;
                cut(edgg[id].u,mx_n);
                cut(edgg[id].v,mx_n);
                link(u,n+eid);
                link(v,n+eid);
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(qs[i].k==1){
            cout<<qs[i].ans<<endl;
        }
    }
    return 0;
}
/*
给一个n个点m条边的图，支持以下操作：
1 询问x到y所有路径中，路径上最大边权的最小值
2 删去一条边
*/
