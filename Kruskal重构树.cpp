#include <bits/stdc++.h>
using namespace std;
int n,m,q,cnt,tot,ver[1000010],hed[1000010],nxt[1000010],root;
int edg[1000010],ffa[1000010],d[1000010],son[1000010];
int size[1000010],dep[1000010],fa[1000010],top[1000010];
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
struct rdd{
	int u,v,c;
}rd[1000010];
bool operator<(rdd a,rdd b){
	return a.c<b.c;
}
int Find(int x){
	if(ffa[x]==x){
		return x;
	}
	return ffa[x]=Find(ffa[x]);
}
void dfs1(int u,int faa){
	fa[u]=faa;
	size[u]=1;
	dep[u]=dep[faa]+1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
	//	dep[v]=dep[u]+1;
		if(v==faa){
			continue;
		}
		dfs1(v,u);
		size[u]+=size[v];
		if(size[son[u]]<size[v]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u]){
		dfs2(son[u],tp);
	}
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==son[u]||v==fa[u]){
			continue;
		}
		dfs2(v,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			u=fa[top[u]];
		}
		else{
			v=fa[top[v]];
		}
	}
	return dep[u]>dep[v]?v:u;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	cnt=n;
//	cout<<cnt;
	for(int i=1;i<=n+m;i++){
		ffa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		rd[++tot].u=a;
		rd[tot].v=b;
		rd[tot].c=c;
	}
	sort(rd+1,rd+m+1);
	for(int i=1;i<=m;i++){
	//	cout<<rd[i].u<<" "<<rd[i].v<<endl;
		int u=Find(rd[i].u),v=Find(rd[i].v);
		//int u,v;
		if(u==v){
			continue;
		}
		add(u,++cnt);
		add(cnt,u);
		add(v,cnt);
		add(cnt,v);
		d[cnt]=rd[i].c;
		ffa[u]=cnt;
		ffa[v]=cnt;
	//	cout<<rd[i].u<<" "<<u<<" -"<<cnt<<"- "<<rd[i].v<<" "<<v<<endl;
	}
/*	for(int i=1;i<=cnt;i++){
		if(fa[i]==i){
			root=i;
		}
	}
	cout<<root<<endl;*/
	for(int i=1;i<=cnt;i++){
		if(ffa[i]==i){
			root=i;
			dfs1(root,0);
			dfs2(root,root);
		}
	}
	/*
	root=7;
	dfs1(root,0);
	dfs2(root,root);
	*/
	cin>>q;
	for(int i=1;i<=q;i++){
		int a,b;
		cin>>a>>b;
		if(Find(a)!=Find(b)){
			cout<<"impossible"<<endl;
			continue;
		}
		cout<<d[lca(a,b)]<<endl;
	}
}
/*
输入格式
第一行包含两个正整数 N 和 M，表示点数和边数。
之后 M 行，每行三个整数 A，B 和 L，
表示顶点 A 和 B 之间有一条危险程度为 L 的边。
顶点从 1 开始标号。
下面一行包含一个正整数 Q，表示询问的数目。
之后 Q 行，每行两个整数 A 和 B，表示询问 A 和 B 之间最危险的边危险程度
的可能最小值。
输出格式
对于每个询问， 在单独的一行内输出结果。如果两个顶点之间不可达，
输出 impossible。

输入 #1
4 5
1 2 5
1 3 2
2 3 11
2 4 6
3 4 4
3
2 3
1 4
1 2

输出 #1
5
4
5

*/
