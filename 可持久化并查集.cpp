#include <bits/stdc++.h>
using namespace std;
int n,m,t;
struct Tree{
	int T[200005],st[200005];//T[]表示i次操作后的根 
	int ls[200005<<5],rs[200005<<5],val[200005<<5];
	int cnt;
	int build(int l,int r){
		int now=++cnt;
		if(l==r){
			val[now]=st[l];
			return now;
		}
		int mid=(l+r)/2;
		ls[now]=build(l,mid);
		rs[now]=build(mid+1,r);
		return now;
	}
	int upload(int pt,int l,int r,int id,int x){//单点赋值 
		int now=++cnt;
		ls[now]=ls[pt];
		rs[now]=rs[pt];
		if(l==r){
			val[now]=x;
			return now;
		}
		int mid=(l+r)/2;
		if(id<=mid){
			ls[now]=upload(ls[pt],l,mid,id,x);
		}else{
			rs[now]=upload(rs[pt],mid+1,r,id,x);
		}
		return now;
	}
	int query(int rt,int l,int r,int id){//单点查询 
		if(l==r){
			return val[rt];
		}
		int mid=(l+r)/2;
		if(id<=mid){
			return query(ls[rt],l,mid,id);
		}else{
			return query(rs[rt],mid+1,r,id);
		}
	}
}fa,siz;
int Find(int x){
	while(fa.query(fa.T[t],1,n,x)!=x){
		x=fa.query(fa.T[t],1,n,x);
	}
	return x;
}
void merge(int x,int y){
	int a=Find(x);
	int b=Find(y);
	if(a==b){
		return;
	}
	int fx=siz.query(siz.T[t],1,n,a),fy=siz.query(siz.T[t],1,n,b);
	if(fx<=fy){
		fa.T[t]=fa.upload(fa.T[t],1,n,a,b);
		siz.T[t]=siz.upload(siz.T[t],1,n,b,fx+fy);
	}else{
		fa.T[t]=fa.upload(fa.T[t],1,n,b,a);
		siz.T[t]=siz.upload(siz.T[t],1,n,a,fx+fy);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa.st[i]=i;
	}
	fa.T[0]=fa.build(1,n);
	for(int i=1;i<=n;i++){
		siz.st[i]=1;
	}
	siz.T[0]=siz.build(1,n);
	int opt,x,y;
	for(t=1;t<=m;t++){
		cin>>opt;
		fa.T[t]=fa.T[t-1];
		siz.T[t]=siz.T[t-1];
		if(opt==1){
			cin>>x>>y;
			merge(x,y);
		}
		else if(opt==2){
			cin>>x;
			fa.T[t]=fa.T[x];
			siz.T[t]=siz.T[x];
		}
		else{
			cin>>x>>y;
			if(Find(x)==Find(y)){
				cout<<1<<endl;
				continue;
			}
			cout<<0<<endl;
		}
	}
	return 0;
}
