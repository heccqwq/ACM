#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e9;
int n,m,tot,root;
struct Splay{
    int fa,ch[3],val,size,sm,add;
}a[1000010];
void Update(int p){
     a[p].sm=a[a[p].ch[0]].sm+a[a[p].ch[1]].sm+a[p].val;
     a[p].size=a[a[p].ch[0]].size+a[a[p].ch[1]].size+1;  
}
void pushdown(int p){
    if(!a[p].add){
    	return ;
	}
    if(a[p].ch[0]){
        a[a[p].ch[0]].add+=a[p].add;
        a[a[p].ch[0]].val+=a[p].add;
        a[a[p].ch[0]].sm+=a[p].add*a[a[p].ch[0]].size;
    }
    if(a[p].ch[1]){
        a[a[p].ch[1]].add+=a[p].add;
        a[a[p].ch[1]].val+=a[p].add;
        a[a[p].ch[1]].sm+=a[p].add*a[a[p].ch[1]].size;
    }
    a[p].add = 0;
}
void push(int x,int goal){
	//cout<<x<<endl;
    if(x!=goal){
        push(a[x].fa,goal);
    }
    pushdown(x);
    return ;
}
void rotate(int x){
    int y=a[x].fa;
    int z=a[y].fa;
    pushdown(z);
    pushdown(y);
    int kid=a[y].ch[1]==x;
    a[z].ch[a[z].ch[1]==y]=x;
    a[x].fa=z;
    a[y].ch[kid]=a[x].ch[kid^1];
    a[a[x].ch[kid^1]].fa=y;
    a[x].ch[kid^1]=y;
    a[y].fa=x;
    Update(y);
    Update(x);
    return ;
}
void splay(int x,int goal){
	push(x,goal);
    while(a[x].fa!=goal){
        int y=a[x].fa;
        int z=a[y].fa;
        if(z!=goal){
            (a[z].ch[1]==y)^(a[y].ch[1]==x)?rotate(x):rotate(y);
        }
        rotate(x);
    }
    if(goal==0){
    	root=x;
	}
    return ;
}
void add(int l,int r,int x){
    splay(l,0);
    splay(r+2,l);
    a[a[r+2].ch[0]].add+=x;
    a[a[r+2].ch[0]].val+=x;
    a[a[r+2].ch[0]].sm+=(a[a[r+2].ch[0]].size)*x;
    Update(r+2);
    Update(l);
    return ;
}
int ask(int l,int r){
    splay(l,0);
    splay(r+2,l);
    return a[a[r+2].ch[0]].sm;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    root=1;
    for(int i=2;i<=n+1;i++){
        cin>>a[i].val;
    }
    for(int i=1;i<=n+2;i++){
        if(i!=1){
            a[i].fa=i-1;
        }
        if(i!=n+2){
            a[i].ch[1]=i+1;
        }
    }
    a[1].val=-inf;
    a[n+2].val=inf;
    for(int i=n+2;i>=1;i--){
        Update(i);
    }
    for(int i=1;i<=m;i++){
        int opt,l,r,x,y;
        cin>>opt;
        if(opt==1){
            cin>>l>>r>>x;
            add(l,r,x);
        }
        if(opt==2){
            cin>>l>>r;
            cout<<ask(l,r)<<endl;
        }
    }
}
