#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[1000010],ansmx[1000010],ansmn[1000010],q[1000010],l,r;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	l=1,r=0;
	for(int i=1;i<=n;i++){
		while(l<=r&&i-q[l]+1>k){
			q[l++]=0;
		}
		while(l<=r&&a[q[r]]>a[i]){
			q[r--]=0;
		}
		q[++r]=i;
		if(i>=k){
			ansmn[i-k+1]=q[l];
		}
	}
	for(int i=1;i<=n-k+1;i++){
		cout<<a[ansmn[i]]<<" ";
	}
	cout<<endl;
	memset(q,0,sizeof(q));
	l=1,r=0;
	for(int i=1;i<=n;i++){
		while(l<=r&&i-q[l]+1>k){
			q[l++]=0;
		}
		while(l<=r&&a[q[r]]<a[i]){
			q[r--]=0;
		}
		q[++r]=i;
		if(i>=k){
			ansmx[i-k+1]=q[l];
		}
	}
	for(int i=1;i<=n-k+1;i++){
		cout<<a[ansmx[i]]<<" ";
	}
}
