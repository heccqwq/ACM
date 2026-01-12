#include <iostream>
using namespace std;
int n,m,a[1000010];
int lowbit(int x){
	return x&(-x);
}
void add(int p,int x){
	for(;p<=n;p+=lowbit(p)){
		a[p]+=x;
	}
	return ;
}
int Ask(int p){
	int ans=0;
	for(;p;p-=lowbit(p)){
		ans+=a[p];
	}
	return ans;
}
int q(int a,int b){
	return Ask(b)-Ask(a-1);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		add(i,x);
	}
	for(int i=1;i<=m;i++){
		int op,a,b;
		cin>>op>>a>>b;
		if(op==1){
			add(a,b);
		}
		if(op==2){
			cout<<q(a,b)<<endl;
		}
	}
}
/*
如题，已知一个数列，你需要进行下面两种操作：

将某一个数加上 x；

求出某区间每一个数的和。
*/
