#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000010],st[100010][30],pw[100010];
int ask(int l,int r){
	int k=log(r-l+1)/log(2);
	return max(st[l][k],st[r-pw[k]+1][k]);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	st[i][0]=a[i];
	}
	int t=log(n)/log(2)+1;
	pw[0]=1;
	for(int i=1;i<=t;i++){
		pw[i]=pw[i-1]*2;
	}
	for(int k=1;k<=t;k++){
		for(int i=1;i+pw[k]-1<=n;i++){
			st[i][k]=max(st[i][k-1],st[i+pw[k-1]][k-1]);
		}
	}
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		cout<<ask(l,r)<<"\n";
	}
	return 0;
}
