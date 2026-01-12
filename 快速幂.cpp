#include <bits/stdc++.h>
#define int long long
using namespace std;
int a,b,p,ans=1,base,cnt;
signed main(){
	cin>>a>>b>>p;
	cnt=b;
	base=a;
	while(b){
		if(b&1){
			ans=(ans%p)*(base%p);
			ans%=p;
		}
		b=b>>1;
		base*=base;
		base%=p;
	}
	cout<<a<<"^"<<cnt<<" mod "<<p<<"=";
	cout<<ans;
}
