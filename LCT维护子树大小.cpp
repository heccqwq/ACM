#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
struct Splay{
    int fa,ch[3],siz,si,rev;
} a[1000010];
bool isroot(int x){
    if(a[a[x].fa].ch[0]==x||a[a[x].fa].ch[1]==x){
        return 0;
    }
    return 1;
}
void pushup(int x) {
    a[x].siz=a[a[x].ch[0]].siz+a[a[x].ch[1]].siz+1+a[x].si;
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
		a[x].si+=a[a[x].ch[1]].siz;
        a[x].ch[1]=y;
        a[x].si-=a[y].siz;
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
    makeroot(y);
    a[x].fa=y;
    a[y].si+=a[x].siz;
    pushup(y);
    return ;
}
void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&a[y].fa==x&&(!a[y].ch[0])){
    	a[x].ch[1]=0;
        a[y].fa=0;
        pushup(x);
        return ;
    }
    return ;
}
void Qus(int x,int y){
	split(x,y);
    cut(x,y);
    makeroot(x);
    makeroot(y);
    pushup(x);
    pushup(y);
    cout<<a[x].siz*a[y].siz<<endl;
    link(x,y);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        a[i].siz=1;
    }
    for(int i=1;i<=m;i++){
        char opt;
		int x,y;
        cin>>opt>>x>>y;
        if(opt=='A'){
            link(x,y);
        }
        if(opt=='Q'){
            Qus(x,y);
        }
    }
}
