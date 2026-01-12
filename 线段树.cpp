#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,w[1000010];
struct SegmentTree{
	int l,r,sm,add;
}a[1000010];
void Spread(int p){
	if(a[p].add){
		a[p*2].add+=a[p].add;
		a[p*2+1].add+=a[p].add;
		a[p*2].sm+=a[p].add*(a[p*2].r-a[p*2].l+1);
		a[p*2+1].sm+=a[p].add*(a[p*2+1].r-a[p*2+1].l+1);
		a[p].add=0;
	}
}
void Build(int p,int l,int r){
	a[p].l=l,a[p].r=r;
	if(l==r){
		a[p].sm=w[l];
		return ;
	}
	int mid=(l+r)/2;
	Build(p*2,l,mid);
	Build(p*2+1,mid+1,r);
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ;
}
void add(int p,int l,int r,int k){
	if(a[p].l>=l&&a[p].r<=r){
		a[p].sm+=(a[p].r-a[p].l+1)*k;
		a[p].add+=k;
		return ;
	}
	Spread(p);
	int mid=(a[p].l+a[p].r)/2;
	if(l<=mid){
		add(p*2,l,r,k);
	}
	if(r>mid){
		add(p*2+1,l,r,k);
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ;
}
int ask(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		return a[p].sm;
	}
	Spread(p);
	int mid=(a[p].l+a[p].r)/2,ans=0;
	if(l<=mid){
		ans+=ask(p*2,l,r);
	}
	if(r>mid){
		ans+=ask(p*2+1,l,r);
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	Build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt,x,l,r;
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>x;
			add(1,l,r,x);
		}
		if(opt==2){
			cout<<ask(1,l,r)<<endl;
		}
	}
}
