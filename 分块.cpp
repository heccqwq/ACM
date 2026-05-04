#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[300010],st[300010],ed[300010],pos[300010],add[300010];
void change(int l,int r,int d){
	int p=pos[l],q=pos[r];
	if(p==q){
		for(int i=l;i<=r;i++){
			a[i]+=d;
		}
	}
	else{
		for(int i=p+1;i<=q-1;i++){
			add[i]+=d;
		}
		for(int i=l;i<=ed[p];i++){
			a[i]+=d; 
		}
		for(int i=st[q];i<=r;i++){
			a[i]+=d;
		}
	}
}
int query(int r){
	int q=pos[r];
    int ans=0;
    ans=a[r]+add[q];
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int len=sqrt(n);
	int t=n/len;
	if(n%len){
		t++;	
	}
	for(int i=1;i<=t;i++){
		st[i]=(i-1)*len+1;
		ed[i]=i*len;
	}
	ed[t]=n;
	for(int i=1;i<=n;i++){
		pos[i]=(i-1)/len+1;
	}
    m=n;
	while(m--){
		int o,x,y,k;
		cin>>o>>x>>y>>k;
		if(o==0){
			change(x,y,k);
		}
		else{
			cout<<query(y)<<endl;
		}
	} 
	return 0;
}

