#include <bits/stdc++.h>
using namespace std;
int nxt[1000010],la,lb;
char a[1000010],b[1000010];
int main(){
	ios::sync_with_stdio(0);
	cin>>(a+1);
	cin>>(b+1);
	la=strlen(a+1);
	lb=strlen(b+1);
	for(int i=2,j=0;i<=lb;i++){
		while(j!=0&&b[j+1]!=b[i]){
			j=nxt[j];
		}
		if(b[j+1]==b[i]){
			j++;
		}
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=la;i++){
		while(j!=0&&b[j+1]!=a[i]){
			j=nxt[j];
		}
		if(b[j+1]==a[i]){
			j++;
		}
		if(j==lb){
			cout<<i-lb+1<<endl;
		}
	}
	for(int i=1;i<=lb;i++){
		cout<<nxt[i]<<" ";
	}
}
/*
给出两个字符串 s 
1，s 2，若 s 1的区间 [l,r] 子串与 s2完全相同，则称 s 2在 s 1中出现了，其出现位置为 l。
现在请你求出 s 2在 s 1中所有出现的位置。
定义一个字符串 s 的 border 为 s 的一个非 s 本身的子串 t，满足 t 既是 s 的前缀，又是 s 的后缀。
对于 s 2
你还需要求出对于其每个前缀 s 的最长 border t 的长度。
输入格式
第一行为一个字符串，即为 s 1
第二行为一个字符串，即为 s 2
输出格式
首先输出若干行，每行一个整数，按从小到大的顺序输出 s 2在 s1中出现的位置。
最后一行输出|s 2|个整数，第 i 个整数表示 s 
2的长度为 i 的前缀的最长 border 长度。
*/
