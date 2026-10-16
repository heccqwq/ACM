#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,w[1000010],y[1000010],ans;
struct SegmentTree{
	int l,r,sm,add;
}a[5000050];
struct Line{
	int y1,y2,x,mark;
}l[1000010];
bool cmp(Line a,Line b){
	return a.x<b.x;
}
void Build(int p,int l,int r){
	a[p].l=l,a[p].r=r;
	a[p].sm=0;
	a[p].add=0;
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	Build(p*2,l,mid);
	Build(p*2+1,mid+1,r);
}
void Update(int p){
	if(a[p].add>0){
		a[p].sm=y[a[p].r+1]-y[a[p].l];
		return ;
	}
	if(a[p].l==a[p].r){
		a[p].sm=0;
		return ;
	}
	a[p].sm=a[p*2].sm+a[p*2+1].sm;
	return ;
}
void change(int p,int l,int r,int k){
	if(l<=a[p].l&&a[p].r<=r){
		a[p].add+=k;
		Update(p);
		return;
	}
	int mid=(a[p].l+a[p].r)/2;
	if(l<=mid){
		change(p*2,l,r,k);
	}
	if(r>mid){
		change(p*2+1,l,r,k);
	}
	Update(p);
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		y[i*2-1]=y1;
		y[i*2]=y2;
		l[i*2-1]={y1,y2,x1,1};
		l[i*2]={y1,y2,x2,-1};
	}
	n*=2;
	sort(y+1,y+n+1);
	sort(l+1,l+n+1,cmp);
	int cnt=unique(y+1,y+n+1)-y-1;
	Build(1,1,cnt-1);
	for(int i=1;i<n;i++){
		int y1=lower_bound(y+1,y+cnt+1,l[i].y1)-y;
		int y2=lower_bound(y+1,y+cnt+1,l[i].y2)-y-1;
		change(1,y1,y2,l[i].mark);
		ans+=a[1].sm*(l[i+1].x-l[i].x);
	}
	cout<<ans<<endl;
	return 0;
}
