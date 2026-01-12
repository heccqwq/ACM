#include <iostream>
#include <cstdio>
using namespace std;
long long n,p[10000010];
long long t[10000010][2],s[10000010],top;
long long ans1,ans2;
inline long long read()
{
	long long f=1,x=0;
	char c=getchar();
	while(c!='-'&&(c<'0'||c>'9')) c=getchar();
	while(c=='-') f=-f,c=getchar();
	while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f*x;
}
int main(){
//	ios::sync_with_stdio(0);
	n=read();
	for(int i=1;i<=n;i++){
		//cin>>p[i];
		p[i]=read();
	}
	for(int i=1;i<=n;i++){
		while(top&&p[s[top]]>p[i]){
			t[i][0]=s[top--];
		}
		t[s[top]][1]=i;
		s[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans1^=i*(t[i][0]+1);
		ans2^=i*(t[i][1]+1);
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}
/*
题目描述
给定一个 1～n 的排列 p，构建其笛卡尔树。
即构建一棵二叉树，满足：
每个节点的编号满足二叉搜索树的性质。
节点 i 的权值为 p i，每个节点的权值满足小根堆的性质。
*/
