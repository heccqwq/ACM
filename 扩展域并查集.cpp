#include <bits/stdc++.h>
using namespace std;
int n,m,tot,fa[100010],b[100010];
struct node{
	int x,y;
	string op;
}a[100010];
int Find(int x){
	if(x==fa[x]){
		return x;
	}
	return fa[x]=Find(fa[x]);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].x>>a[i].y;
		cin>>a[i].op;
		a[i].x--;
		b[++tot]=a[i].x;
		b[++tot]=a[i].y;
	}
	sort(b+1,b+1+tot);
	int cnt=unique(b+1,b+1+tot)-b-1;
	for(int i=1;i<=cnt*2;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		a[i].x=lower_bound(b+1,b+1+cnt,a[i].x)-b;
		a[i].y=lower_bound(b+1,b+1+cnt,a[i].y)-b;
	}
	for(int i=1;i<=m;i++){
		if(a[i].op=="even"){
			if(Find(a[i].x)==Find(a[i].y+cnt)){
				printf("%d",i-1);
				return 0;
			}
			fa[Find(a[i].x)]=Find(a[i].y);
			fa[Find(a[i].x+cnt)]=Find(a[i].y+cnt);
		}
		else{
			if(Find(a[i].x)==Find(a[i].y)){
				printf("%d",i-1);
				return 0;
			}
			fa[Find(a[i].x)]=Find(a[i].y+cnt);
			fa[Find(a[i].x+cnt)]=Find(a[i].y);
		}
	}
	cout<<m;
	return 0;
}
/*
Alice 和 Bob 在玩一个游戏：他写一个由 0 和 1 组成的序列。
Alice 选其中的一段（比如第 3 位到第 5 位），问他这段里面有奇数个 1 还是偶数个 1。
Bob 回答你的问题，然后 Alice 继续问。
Alice 要检查 Bob 的答案，指出在 Bob 的第几个回答一定有问题。
有问题的意思就是存在一个 01 序列满足这个回答前的所有回答，
而且不存在序列满足这个回答前的所有回答及这个回答。

输入格式
第 1 行一个整数 n，是这个 01 序列的长度。
第 2 行一个整数 m，是问题和答案的个数。
第 3 行开始是问题和答案，每行先有两个整数，表示你询问的段的开始位置和结束位置。
然后是 Bob 的回答。odd表示有奇数个 1，even 表示有偶数个 1。
输出格式
输出一行，一个数 x，表示存在一个 01 序列满足第 1 到第 x 个回答，但是不存在序列满足第 1 到第 x+1 个回答。
如果所有回答都没问题，你就输出所有回答的个数。

*/
