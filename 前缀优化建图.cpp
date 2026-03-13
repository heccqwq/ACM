#include <bits/stdc++.h>
using namespace std;
int n,m,k,ver[8000080],nxt[8000050],hed[8000050],low[8000050],dfn[8000050];
int ins[8000080],st[8000080],tot,tp,smscc,cnt,p[8000050],blg[8000050];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u){
	low[u]=dfn[u]=++cnt;
	ins[u]=1;
	st[++tp]=u;
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
		int v;
		++smscc;
		do{
			v=st[tp--];
			blg[v]=smscc;
			ins[v]=0;
		}while(v!=u);
	}
	return ;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a+n,b);
		add(b+n,a);
	}
	for(int i=1;i<=k;i++){
		int w;
		cin>>w;
		for(int j=1;j<=w;j++){
			cin>>p[j];
			add(p[j]+2*n,p[j]+n);
			add(p[j]+3*n,p[j]+n);
		}
		for(int j=1;j<w;j++){
			add(p[j+1]+2*n,p[j]+2*n);
			add(p[j]+3*n,p[j+1]+3*n);
			add(p[j],p[j+1]+3*n);
			add(p[j+1],p[j]+2*n);
		}
	}
	for(int i=1;i<=2*n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(blg[i]==blg[i+n]){
			cout<<"NIE"<<endl;
			return 0;
		}
	}
	cout<<"TAK"<<endl;
	return 0;
}
/*
题目描述
n 个点 m 条边的无向图被分成 k 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分恰有一个关键点，且每条边至少有一个端点是关键点。

输入格式
第一行三个整数 n,m,k。

接下来 m 行，每行两个整数 a,b，表示有一条 a,b 间的边。

接下来 k 行，每行第一个整数为 w，表示这个部分有 w 个点；接下来 w 个整数，
为在这个部分中的点的编号。

输出格式
若可能选出请输出 TAK，否则输出 NIE。
*/
