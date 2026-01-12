#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,q,cnt[5000050],tot,ch[3000050][70];
int Change(char a){
	if('A'<=a&&'Z'>=a){
		return (int)(a-'A')+1;
	}
	if('a'<=a&&'z'>=a){
		return (int)(a-'a')+27;
	}
	return (int)(a-'0'+53);
}
int Ask(string s){
	int p=0;
	for(int i=0;i<s.size();i++){
		int c=Change(s[i]);
		if(!ch[p][c]){
			return 0;
		}
		p=ch[p][c];
	}
	return cnt[p];
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=0;i<=tot;i++){
			cnt[i]=0;
			for(int j=0;j<=70;j++){
				ch[i][j]=0;
			}
		}
		tot=0;
		for(int i=1;i<=n;i++){
			string s;
			cin>>s;
			int p=0;
			for(int i=0;i<s.size();i++){
				int c=Change(s[i]);
				if(!ch[p][c]){
					ch[p][c]=++tot;
				}
				p=ch[p][c];
				cnt[p]++;
			}
		}
		for(int i=1;i<=q;i++){
			string s;
			cin>>s;
			cout<<Ask(s)<<endl;
		}
	}
}
