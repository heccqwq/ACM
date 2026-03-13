#include <bits/stdc++.h>
using namespace std;
int T,n,m,ver[100050],hed[100050],nxt[100050],tot,dfn[100050],low[100050];
int blg[100050],cnt,smscc,G[5050];
stack<int> s;
struct edge{
	int u,v;
}eg[100050];
bool operator <(edge a,edge b){
	if(a.u==b.u){
		return a.v<b.v;
	}
	return a.u<b.u;
}
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int u){
	s.push(u);
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!blg[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		int x;
		++smscc;
		do{
			x=s.top();
			s.pop();
			blg[x]=smscc;
		}while(x!=u);
	}
}
void clear(){
	memset(hed,0,sizeof(hed));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(blg,0,sizeof(blg));
	tot=smscc=cnt=0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		clear();
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			eg[i]=(edge){u,v};
		}
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			G[x]=i;
		}
		if(m>3*n-6){
			cout<<"NO"<<endl;
			continue;
		}
		for(int i=1;i<=m;i++){
			eg[i].u=G[eg[i].u];
			eg[i].v=G[eg[i].v];
			if(eg[i].u>eg[i].v){
				swap(eg[i].u,eg[i].v);
			}
		}
		sort(eg+1,eg+m+1);
		for(int i=1;i<m;i++){
			for(int j=i+1;j<=m;j++){
				if(eg[i].u<eg[j].u&&eg[j].u<eg[i].v&&eg[i].v<eg[j].v){
					add(i+m,j);
					add(j+m,i);
					add(i,j+m);
					add(j,i+m);
				}
			}
		}
		for(int i=1;i<=(m<<1);i++){
			if(!dfn[i]){
				tarjan(i);
			}
		}
		bool fl=1;
		for(int i=1;i<=m;i++){
			if(blg[i]==blg[i+m]){
				fl=0;
				break;
			}
		}
		if(fl){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
/*
若能将无向图 G=(V,E) 画在平面上使得任意两条无重合顶点的边不相交，
则称 G 是平面图。判定一个图是否为平面图的问题是图论中的一个重要问题。
现在假设你要判定的是一类特殊的图，图中存在一个包含所有顶点的环，
即存在哈密顿回路。

输入格式
输入文件的第一行是一个正整数 T，表示数据组数 (每组数据描述一个需要判定的图)。
接下来从输入文件第二行开始有 T 组数据，每组数据的第一行是
用空格隔开的两个正整数 N 和 M，分别表示对应图的顶点数和边数。
紧接着的 M 行，每行是用空格隔开的两个正整数 u 和 v (1≤u,v≤N)，
表示对应图的一条边 (u,v), 输入的数据保证所有边仅出现一次。
每组数据的最后一行是用空格隔开的 N 个正整数，从左到右表示对应图中的
一个哈密顿回路：V1,V2,…,VN，即对任意 i=j 有 Vi=Vj且对任意 1≤i≤N
有 (Vi,Vi+1)∈E 及 (V1,VN)∈E。
输入的数据保证 100% 的数据满足 T≤100,3≤N≤200,M≤10000。

输出格式
包含 T 行，若输入文件的第 i 组数据所对应图是平面图，则在第 i 行输出 YES，
否则在第 i 行输出 NO，注意均为大写字母

*/
