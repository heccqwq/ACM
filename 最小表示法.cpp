#include <bits/stdc++.h>
using namespace std;
int n,ans;
char s[20000010];
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>(s+1);
	for(int i=1;i<=n;i++){
		s[n+i]=s[i];
	}
	int i=1,j=2,k;
	while(i<=n&&j<=n){
		for(k=0;k<n&&s[i+k]==s[j+k];k++){
		}
		if(k==n){
			break;
		}
		if(s[i+k]>s[j+k]){
			i=i+k+1;
			if(i==j){
				i++;
			}
		}
		else{
			j=j+k+1;
			if(i==j){
				j++;
			}
		}
	}
	ans=min(i,j);
	for(int i=0;i<n;i++){
		cout<<s[i+ans];
	}
}
/*
若长度为 n 的字符串 s 中可以选择一个位置 i，使得  
si...sns1...s isi-1=t，则称 s 与 t 循环同构
字符串 s 的最小表示为与 s 循环同构的所有字符串中字典序最小的字符串。
给定一个长度为 n 的字符串 s，请求出 s 的最小表示。
*/
