#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int root,tot,n,m,t[100005],pos[100005];
struct Splay{
    int fa,ch[2],val,size;
}a[100005];
void Update(int x){
    if(!x){
    	return;
	}
    a[x].size=a[a[x].ch[0]].size+a[a[x].ch[1]].size+1;
}
int build_tree(int fa,int l,int r){
    if(l>r) return 0;
    int mid=(l+r)>>1;
    int now=++tot;
    a[now].ch[0]=a[now].ch[1]=0;
    a[now].fa=fa;
    a[now].val=t[mid];
    a[now].size=1;
    if(t[mid]>=1 && t[mid]<=n) pos[t[mid]]=now;
    a[now].ch[0]=build_tree(now,l,mid-1);
    a[now].ch[1]=build_tree(now,mid+1,r);
    Update(now);
    return now;
}
void rotate(int x){
    int y=a[x].fa;
	int z=a[y].fa;
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
    while(a[x].fa!=goal){
        int y=a[x].fa,z=a[y].fa;
        if(z!=goal){
            if((a[z].ch[1]==y)==(a[y].ch[1]==x)) rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(goal==0){
    	root=x;
	}
}
int kth(int k){
    int cur=root;
    while(cur){
        if(k<=a[a[cur].ch[0]].size){
            cur=a[cur].ch[0];
        }else{
            k-=a[a[cur].ch[0]].size+1;
            if(k==0) return cur;
            cur=a[cur].ch[1];
        }
    }
    return 0;
}
int get_rank(int x){
    splay(x,0);
    return a[a[x].ch[0]].size;
}
void Top(int x){
    int loc=pos[x];
    int rk=get_rank(loc);
    if(rk==1){
    	return;
	}
    splay(loc,0);
    int pre=kth(rk),nxt=kth(rk+2);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=0;
    a[loc].fa=0;
    a[loc].ch[0]=a[loc].ch[1]=0;
    Update(root);
    Update(a[root].ch[1]);
    
    pre=kth(1);
    nxt=kth(2);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=loc;
    a[loc].fa=a[root].ch[1];
    Update(root);
    Update(a[root].ch[1]);
}
void Bottom(int x){
    int loc=pos[x];
    int rk=get_rank(loc);
    if(rk==n){
    	return;
	}
    splay(loc,0);
    int pre=kth(rk),nxt=kth(rk+2);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=0;
    a[loc].fa=0;
    a[loc].ch[0]=a[loc].ch[1]=0;
    Update(root);
    Update(a[root].ch[1]);
    
    pre=kth(n);
    nxt=kth(n+1);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=loc;
    a[loc].fa=a[root].ch[1];
    Update(root);
    Update(a[root].ch[1]);
}
void Insert(int x,int t){
    if(t==0) return;
    int loc=pos[x];
    int rk=get_rank(loc);
    int target=rk+t;
    splay(loc,0);
    int pre=kth(rk),nxt=kth(rk+2);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=0;
    a[loc].fa=0;
    a[loc].ch[0]=a[loc].ch[1]=0;
    Update(root);
    Update(a[root].ch[1]);
    
    pre=kth(target);
    nxt=kth(target+1);
    splay(pre,0);
    splay(nxt,pre);
    a[a[root].ch[1]].ch[0]=loc;
    a[loc].fa=a[root].ch[1];
    Update(root);
    Update(a[root].ch[1]);
}
int Ask(int x){
    int loc=pos[x];
    int rk=get_rank(loc);
    return rk-1;
}
int Query(int x){
    int loc=kth(x+1);
    return a[loc].val;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    t[1]=-inf;
    for(int i=1;i<=n;i++){
    	cin>>t[i+1];
	}
    t[n+2]=inf;
    root=build_tree(0,1,n+2);
    for(int i=1;i<=m;i++){
        string opt;
        int x,t;
        cin>>opt;
        if(opt=="Top"){
            cin>>x;
            Top(x);
        }
		if(opt=="Bottom"){
            cin>>x;
            Bottom(x);
        }
		if(opt=="Insert"){
            cin>>x>>t;
            Insert(x,t);
        }
		if(opt=="Ask"){
            cin>>x;
            cout<<Ask(x)<<endl;
        }
		if(opt=="Query"){
            cin>>x;
            cout<<Query(x)<<endl;
        }
    }
    return 0;
}
/*
第一行有两个整数，分别表示书的个数 n 以及命令条数 m。

第二行有 n 个整数，第 i 个整数表示初始时从上向下书第 i 本书的编号 pi
接下来 m 行，每行表示一个操作。每行初始时有一个字符串 op。

若 op 为 Top，则后有一个整数 s，表示把编号为 s 的书放在最上面。
若 op 为 Bottom，则后有一个整数 s，表示把编号为 s 的书放在最下面。
若 op 为 Insert，则后有两个整数 s,t，表示若编号为 s 的书上面有 x 本书，
则放回这本书时他的上面有 x+t 本书。
若 op 为 Ask，则后面有一个整数 s，表示询问编号为 s 的书上面有几本书。
若 op 为 Query，则后面有一个整数 s，询问从上面起第 s 本书的编号。
*/
