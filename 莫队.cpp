#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,size,ans[100010],a[1000010],cnt[1000010],l=1,r,sm;
struct Q{
	int l,r,id;
}q[1000010];
bool operator<(Q a,Q b){
	if(a.l/size==b.l/size){
		return a.r<b.r;
	}
	return a.l/size<b.l/size;
}
void Del(int p){
	sm-=(cnt[a[p]]*cnt[a[p]]);
	cnt[a[p]]--;
	sm+=(cnt[a[p]]*cnt[a[p]]);
}
void Add(int p){
	sm-=(cnt[a[p]]*cnt[a[p]]);
	cnt[a[p]]++;
	sm+=(cnt[a[p]]*cnt[a[p]]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>k;
	size=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	for(int i=1;i<=m;i++){
		while(l<q[i].l){
			Del(l++);
		}
		while(l>q[i].l){
			Add(--l);
		}
		while(r<q[i].r){
			Add(++r);
		}
		while(r>q[i].r){
			Del(r--);
		}
		ans[q[i].id]=sm;
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
}
/*
题目描述
小 B 有一个长为 n 的整数序列 a，值域为 [1,k]。
他一共有 m 个询问，每个询问给定一个区间 [l,r]，求Ci平方和 
  Ci表示数字 i 在 [l,r] 中的出现次数。

小 B 请你帮助他回答询问。

输入格式
第一行三个整数 n,m,k。

第二行 n 个整数，表示小 B 的序列。

接下来的 m 行，每行两个整数 l,r。

输出格式
输出 m 行，每行一个整数，对应一个询问的答案。
*/
