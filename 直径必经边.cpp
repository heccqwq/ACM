#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> a[200001],b[200001];
int n,ans,lst[200001],uu,vv,nxt[200001],dis[200001];
int mmm[200001],mx,vis[200001];
void dfs1(int u,int fa,int d){
    if(d>mx){
		mx=d;
		uu=u;
	}
    for(int i=0;i<a[u].size();i++){
    	if((!vis[a[u][i]])&&(a[u][i]!=fa)){
            vis[a[u][i]]=1;
            dfs1(a[u][i],u,d+b[u][i]);
        }
	}
}
void dfs2(int u,int fa,int d){
    lst[u]=fa;
    dis[u]=d;
    if(d>mx){
		mx=d;
		vv=u;
	}
    for(int i=0;i<a[u].size();i++){
    	if((!vis[a[u][i]])&&(a[u][i]!=fa)){
            vis[a[u][i]]=1;
            dfs2(a[u][i],u,d+b[u][i]);
        }
	}
}
signed main(){
	ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y,z;
        cin>>x>>y>>z;
        a[x].push_back(y);
        b[x].push_back(z);
        a[y].push_back(x);
        b[y].push_back(z);
    }
    memset(vis,0,sizeof(vis));
	mx=0;
    dfs1(1,0,0);
    memset(vis,0,sizeof(vis));
	mx=0;
    dfs2(uu,0,0);
    cout<<dis[vv]<<endl;
    memset(vis,0,sizeof(vis));
    for(int i=vv;i;i=lst[i]){
    	vis[i]=1;
	}
    for(int i=vv;i;i=lst[i]){
        mx=0;
        dfs1(i,0,0);
        mmm[i]=mx;
    }
    int j=vv;
    for(int i=lst[vv];i;i=lst[i]){
    	nxt[i]=j;
		j=i;
	}
	int i=j;
    while(i){
    	if(dis[vv]-dis[i]==mmm[i]){
    		break;
		}
		i=nxt[i];
	}
    while(i){
        if(dis[i]==mmm[i]){
        	break;
		}
        ans++;
		i=lst[i];
    }
    cout<<ans<<endl;
    return 0;
}
/*
树：无回路且连通的无向图，每条边都有正整数的权值来表示其长度。
如果一棵树有 N 个节点，可以证明其有且仅有 N-1条边。
路径：一棵树上，任意两个节点之间最多有一条简单路径。
称 dis(a,b) 为 a,b 两个节点间的距离。
直径：一棵树上，最长的路径为树的直径。树的直径可能不是唯一的。
现在小 Q 想知道，对于给定的一棵树，其直径的长度是多少，
以及有多少条边满足所有的直径都经过该边。

输入格式
第一行包含一个整数 N，表示节点数。
接下来 N-1 行，每行三个整数 a,b,c，表示点 a 和点 b 之间有一条长度为 c 的无向边。
输出格式
共两行。第一行一个整数，表示直径的长度。
第二行一个整数，表示被所有直径经过的边的数量。

*/
