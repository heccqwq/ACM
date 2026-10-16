#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m1,m2,ans,b1[1000010],b2[1000010];
struct SegmentTree{
	int l,r,sm,add;
}t1[5000050],t2[5000050];
struct Line{
	int l,r,s,mark;
	bool operator<(const Line &a)const{
		return s==a.s?mark>a.mark:s<a.s;
	}
}l1[5000050],l2[5000050];
bool cmp(Line a,Line b){
	if(a.s==b.s){
		return a.mark>b.mark;
	}
	return a.s<b.s;
} 
void Build(SegmentTree *t,int p,int l,int r){
	t[p].l=l,t[p].r=r;
	t[p].sm=0;
	t[p].add=0;
	if(l==r)return;
	int mid=(l+r)/2;
	Build(t,p*2,l,mid);
	Build(t,p*2+1,mid+1,r);
}
void Update(SegmentTree *t,int *b,int p){
	if(t[p].add>0){
		t[p].sm=b[t[p].r+1]-b[t[p].l];
		return;
	}
	if(t[p].l==t[p].r){
		t[p].sm=0;
		return;
	}
	t[p].sm=t[p*2].sm+t[p*2+1].sm;
}
void change(SegmentTree *t,int *b,int p,int l,int r,int k){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].add+=k;
		Update(t,b,p);
		return;
	}
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid){
		change(t,b,p*2,l,r,k);
	}
	if(r>mid){
		change(t,b,p*2+1,l,r,k);
	}
	Update(t,b,p);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		l1[i*2-1]={a,c,b,1};
		l1[i*2]={a,c,d,-1};
		l2[i*2-1]={b,d,a,1};
		l2[i*2]={b,d,c,-1};
		b1[i*2-1]=a,b1[i*2]=c;
		b2[i*2-1]=b,b2[i*2]=d;
	}
	n<<=1;
	sort(l1+1,l1+n+1);
	sort(l2+1,l2+n+1);
	sort(b1+1,b1+n+1);
	sort(b2+1,b2+n+1);
	m1=unique(b1+1,b1+n+1)-(b1+1);
	m2=unique(b2+1,b2+n+1)-(b2+1);
	Build(t1,1,1,m1-1);
	Build(t2,1,1,m2-1);
	int temp1=0,temp2=0;
	for(int i=1;i<=n;i++){
		int L1=lower_bound(b1+1,b1+m1+1,l1[i].l)-b1;
		int R1=lower_bound(b1+1,b1+m1+1,l1[i].r)-b1;
		int L2=lower_bound(b2+1,b2+m2+1,l2[i].l)-b2;
		int R2=lower_bound(b2+1,b2+m2+1,l2[i].r)-b2;
		change(t1,b1,1,L1,R1-1,l1[i].mark);
		change(t2,b2,1,L2,R2-1,l2[i].mark);
		ans+=abs(t1[1].sm-temp1)+abs(t2[1].sm-temp2);
		temp1=t1[1].sm,temp2=t2[1].sm;
	}
	cout<<ans<<endl;
	return 0;
}
