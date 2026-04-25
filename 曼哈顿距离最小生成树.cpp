#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,m,fr[1000010],f[1000010],s[1000010],b[1000010];
queue<pair<int,int> > q;
struct point{
	int x,y,i;
}a[1000010];
int find(int p){
	if(f[p]==p){
		return p;
	}
	return f[p]=find(f[p]);
}
struct node{
	int v,i;
	void init(){
		v=-inf,i=0;
	}
	bool operator >(const node &_a)const{
		return v>=_a.v;
	}
}c[1000010][2],e[1000010];
void merge(int u,int v){
	u=find(u),v=find(v);
	if(s[u]<s[v]){
		swap(u,v);
	}
	s[u]+=s[v];
	f[v]=u;
}
bool id(node _a,node _b){
	return find(_a.i)==find(_b.i);
}
int lowbit(int x){
	return x&-x;
}
void upd(int p,int i){
	node k=(node){b[a[i].y]+a[i].x,a[i].i};
	while(p<=m){
		if(k>c[p][0]){
			if(!id(k,c[p][0])){
				c[p][1]=c[p][0];
			}
			c[p][0]=k;
		}
		else if(!id(k,c[p][0])&&k>c[p][1]){
			c[p][1]=k;
		}
		p+=lowbit(p);
	}
}
node query(int p,int i){
	node sum;sum.init();
	while(p){
		node x=(find(c[p][0].i)==i?c[p][1]:c[p][0]);
		sum=(x>sum?x:sum);
		p-=lowbit(p);
	}
	return sum;
}
void solve(){
	for(int i=1;i<=m;i++){
		c[i][0].init();
		c[i][1].init();
	}
	for(int i=1;i<=n;i++){
		int id=a[i].i;
		node k=query(a[i].y,find(id));
		k.v=llabs(b[a[i].y]+a[i].x-k.v);
		if(e[find(id)]>k&&k.i){
			e[find(id)]=k;
			fr[find(id)]=id;
		}
		upd(a[i].y,i);
	}
}
bool cmp(point _a,point _b){
	return _a.x<_b.x;
}
void solve_x(){
	solve(); 
	for(int i=1;i<=n;i++){
		a[i].x=-a[i].x;
	}
	reverse(a+1,a+1+n);
} 
void solve_y(){
	solve();
	for(int i=1;i<=n;i++){
		a[i].y=m-a[i].y+1;
	}
	for(int i=1;i<=m;i++){
		b[i]=-b[i];
	}
	reverse(b+1,b+1+m);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].i=i;
		b[i]=a[i].y;
		f[i]=i;
		s[i]=1;
	}
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		a[i].y=lower_bound(b+1,b+1+m,a[i].y)-b;
	}
	sort(a+1,a+1+n,cmp);
	int sum=0;
	while(1){
		for(int i=1;i<=n;i++){
			e[i]=(node){inf,0};
		}
		for(int i=0;i<2;i++){
			solve_x();
			solve_y();
		}
		for(int i=1;i<=n;i++){
			int id=a[i].i;
			if(!e[id].i||find(e[id].i)==find(id)){
				continue;
			}
			merge(id,e[id].i);
			q.push({fr[id],e[id].i});
			sum+=e[id].v;
			fr[id]=0;
		}
		if(q.size()==n-1){
			break;
		}
	}
	cout<<sum<<"\n";
	while(q.size()){
		cout<<q.front().first<<" "<<q.front().second<<endl;
		q.pop();
	}
	return 0;
}
/*
给定平面上的 n 个点 (x1,y1),(x2,y2),…,(xn,y n)。考虑一个有 n 个结点的完全图，
对于 1≤u,v≤n，结点 u,v 之间有一条权值为 ∣xu-xv∣+∣yu-yv∣的边。
请求出该图的最小生成树。
*/
