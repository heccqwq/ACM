#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,type,ans,f[5000005],d[5000005],p[5000005];
int make_prufer(int n){
    for(int i=1;i<n;++i){
    	cin>>f[i];
		d[f[i]]++;
	}
    for(int i=1,j=1;i<=n-2;i++,j++){
		while(d[j]){
			j++;
		}
	    p[i]=f[j];
		while(i<=n-2&&!--d[p[i]]&&p[i]<j){
			p[i+1]=f[p[i]];
			i++;
		}
	}
	for(int i=1;i<=n-2;i++){
		ans^=(long long)i*p[i];
	}
	return ans;
}
int make_fa(int n){
	for(int i=1;i<=n-2;++i){
		cin>>p[i];
		d[p[i]]++;
	}
	p[n-1]=n;
	for(int i=1,j=1;i<n;i++,j++){
		while(d[j]){
			j++;
		}
		f[j]=p[i];
		while(i<n&&!--d[p[i]]&&p[i]<j){
			f[p[i]]=p[i+1];
			i++;
		}
	}
	for(int i=1;i<n;i++){
		ans^=(long long)i*f[i];
	}
    return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>type;
	if(type==1){
		cout<<make_prufer(n);
	}
	if(type==2){
		cout<<make_fa(n);
	}
	return 0;
}
/*
实现 Prüfer 序列和无根树的相互转化。
为方便你实现代码，尽管是无根树，我们在读入时仍将 n 设为其根。
对于一棵无根树，设 f 1…n-1为其父亲序列（fi表示 i 在 n 为根时的父亲）
设 p 1…n-2为其 Prüfer 序列。
另外，对于一个长度为 m 的序列 a 1…m ，我们设其权值为全部xor值 
输入格式
第一行两个整数 n,m，表示树的点数和转化类型。
若 m=1，第二行一行 n?1 个整数，表示父亲序列。
若 m=2，第二行一行 n?2 个整数，表示 Prüfer 序列。
输出格式
若 m=1，一行一个整数，表示给出的父亲序列对应的 Prüfer 序列的权值。
若 m=2，一行一个整数，表示给出的 Prüfer 序列对应的父亲序列的权值。
*/
