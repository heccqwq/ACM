#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,ss,tt,tot=1,ver[1000010],hed[1000010],nxt[1000010],edg[1000010];
int dfn[1000010],low[1000010],d[1000010],now[1000010],cnt,smscc;
int flow,maxflow,ins[1000010],blg[1000010],frm[1000010];
stack<int> s;
void add(int a,int b,int c){
	ver[++tot]=b,frm[tot]=a,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
	ver[++tot]=a,frm[tot]=b,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0;
}
bool bfs(){
	queue<int> q;
	for(int i=1;i<=n;i++){
		d[i]=0;
	}
	d[ss]=1;
	q.push(ss);
	now[ss]=hed[ss];
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=hed[u];i;i=nxt[i]){
			int v=ver[i];
			if((!edg[i])||(d[v])){
				continue;
			}
			d[v]=d[u]+1;
			now[v]=hed[v];
			q.push(v);
		}
	}
	if(d[tt]){
		return 1;
	}
	return 0;
}
int dinic(int u,int flow){
	if(u==tt){
		return flow;
	}
	int i,k,rest=flow;
	for(i=now[u];i&&rest;i=nxt[i]){
		int v=ver[i];
		if((!edg[i])||(d[v]!=d[u]+1)){
				continue;
		}
		k=dinic(v,min(edg[i],rest));
		if(!k){
			d[v]=0;
			continue;
		}
		rest-=k;
		edg[i]-=k;
		edg[i^1]+=k;
	}
	now[u]=i;
	return flow-rest;
}
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	ins[u]=1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!edg[i]){
			continue;
		}
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[v],low[u]);
		}
		else if(ins[v]){
			low[u]=min(dfn[v],low[u]);
		}
	}
	if(dfn[u]==low[u]){
		++smscc;
		int v;
		do{
			v=s.top();
			s.pop();
			ins[v]=0;
			blg[v]=smscc;
		}while(v!=u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>ss>>tt;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	while(bfs()){
		while(flow=dinic(ss,inf)){
			maxflow+=flow;
		}
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=2;i<=tot;i+=2){
		int u=frm[i],v=ver[i];
		if(edg[i]==0&&blg[u]!=blg[v]){
			cout<<"1 ";
			if(blg[u]==blg[ss]&&blg[v]==blg[tt]){
				cout<<"1"<<endl;
				continue;
			}
			cout<<"0"<<endl;
			continue;
		}
		cout<<"0 0"<<endl;
	}
	return 0;
}
/*
题目描述
有 N 个点，M 条单向道路。设其中第 i(1≤i≤M) 条道路连接了 vi,ui两个点，
那么点 vi可以通过该道路到达 ui，如果切断这条道路，需要代价 ci。
现在想找出一个路径切断方案，使点 s 不能到达点 t，并且切断路径的代价之和最小。
现在对每条单向道路提出两个问题：

问题一：是否存在一个最小代价路径切断方案，其中该道路被切断？
问题二：是否对任何一个最小代价路径切断方案，都有该道路被切断？
现在请你回答这两个问题。

*/
