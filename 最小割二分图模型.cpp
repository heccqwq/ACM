#include <bists/stdc++.h>
using namespace std;
const int inf=1e9;
int m,n,ver[10000010],hed[10000010],nxt[10000010],edg[10000010];
int tot=1,sm,s,t,d[10000010],now[10000010],a[10000010];
int b[10000010],c[10000010],maxflow;
void add(int a,int b,int c){
    ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot,edg[tot]=c;
    ver[++tot]=a,nxt[tot]=hed[b],hed[b]=tot,edg[tot]=0;
}
bool bfs(){
    queue <int> q;
    memset(d,0,sizeof(d));
    q.push(s);
    d[s]=1,now[s]=hed[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=hed[u];i;i=nxt[i]){
            int v=ver[i];
            if(edg[i]&&(!d[v])){
                d[v]=d[u]+1;
                q.push(v);
                now[v]=hed[v];
                if(v==t){
                    return 1;
                }
            }
        }
    }
    return 0;
}
int dinic(int u,int flow){
    if(u==t){
        return flow;
    }
    int rest=flow,k,i;
    for(i=now[u];i&&rest;i=nxt[i]){
        int v=ver[i];
        if((!edg[i])||(d[v]!=d[u]+1)){
			continue;
		}
        k=dinic(v,min(rest,edg[i]));
        if(!k){
            d[v]=0;
            continue;
        }
        edg[i]-=k;
        edg[i^1]+=k;
        rest-=k;
	}
    now[u]=i;
    return flow-rest;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sm+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		sm+=b[i];
	}
	cin>>m;
	s=0,t=n+2*m+1;
	for(int i=1;i<=n;i++){
		add(s,i,a[i]);
	}
	for(int i=1;i<=n;i++){
		add(i,t,b[i]);
	}
	for(int i=1;i<=m;i++){
		int k,x,y;
		cin>>k;
		cin>>x>>y;
		sm+=x;
		sm+=y;
		add(s,n+i,x);
		add(n+m+i,t,y);
		for(int j=1;j<=k;j++){
			cin>>c[j];
			add(n+i,c[j],inf);
			add(c[j],n+m+i,inf);
		}
	}
	int flow=0;
	while(bfs()){
		while(flow=dinic(s,inf)){
			maxflow+=flow;
		}
	}
	cout<<sm-maxflow;
}
/*
题目描述
小 M 开辟了两块巨大的耕地 A 和 B（你可以认为容量是无穷）
在，第i种作物种植在 A 中种植可以获得 ai的收益，在 B 中种植可以获得 bi的收益
而且某些作物共同种在一块耕地中可以获得额外的收益，共有 m 种作物组合
第i个组合中的作物共同种在 A 中可以获得 c1,i的额外收益，
共同种在 B 中可以获得 c2,i的额外收益。
求种植的最大收益
*/ 
