#include <bits/stdc++.h>
using namespace std;
int n,m,tot,ver[5000010],hed[5000010],nxt[5000010],blg[5000010];
int low[5000010],dfn[5000010],cnt,ins[5000010],smscc;
stack<int> s;
void tarjan(int u){
	low[u]=dfn[u]=++cnt;
	ins[u]=1;
	s.push(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		int k=0;
		smscc++;
		do{
			k=s.top();
			s.pop();
			blg[k]=smscc;
			ins[k]=0;
		}while(k!=u);
	}
}
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
int main(){
	ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
		int a,ca,b,cb;
		cin>>a>>ca>>b>>cb;
		add(a+(ca^1)*n,b+cb*n);
		add(b+(cb^1)*n,a+ca*n);	
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(blg[i]==blg[i+n]){
			cout<<"IMPOSSIBLE";
			return 0;
		}
	}
	cout<<"POSSIBLE"<<endl;
	for(int i=1;i<=n;i++){
		cout<<(blg[i]>blg[i+n])<<" ";
	}
    return 0;
}
/*
有 n 个布尔变量 x ，另有 m 个需要满足的条件，
每个条件的形式都是「x 为 true / false 或 x 为 true / false」
比如 「x1为真或 x3为假」、「x7为假或 x2为假」。
2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。
输入格式
第一行两个整数 n 和 m，意义如题面所述。
接下来 m 行每行 4 个整数 i, a, j, b，表示 「x i为 a 或 x j为 b」(a,b∈{0,1})
输出格式
如无解，输出 IMPOSSIBLE；
否则输出 POSSIBLE，下一行 n 个整数 x （x i∈{0,1}），表示构造出的解。

输入 #1
3 1
1 1 3 0

输出 #1
POSSIBLE
0 0 0

*/
