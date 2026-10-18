//树的直径
/*
若树上所有边边权均为正，则树的所有直径中点重合．
*/
void dfs(int id,int st){
    bool flag=1;
    for (auto x:a[id]){
        if(vis[x]==0){
            vis[x]=1;
            flag=0;
            dfs(x,st+1);
        }
    }
    if(flag&&st>Max){
        Max=st;
        root=id;
    }
} 
void dfs1(int id,int st){
    bool flag=1;
    for (auto x:a[id]){
        if(vis[x]==0){
            vis[x]=1;
            flag=0;
            dfs1(x,st+1);
        }
    }
    if(flag){
        ans=max(ans,st);
    }
}



//树的重心
/*
树的重心如果不唯一则恰有两个相邻重心．删去它们的连边后，树将变为两个大小相同的连通分量．
在一棵树上添加或删除一个叶子，重心最多只移动一条边的距离．
把两树通过一条边相连得到新树，新树的重心在连接原来两棵树的重心的路径上．
有根树的重心一定在根所在的重链上．一棵树的重心一定是根结点重子结点对应子树的重心的祖先．
*/
void dfs(int s,int fa){
    d[s]=1;
    int res=0;
    for(int i=0;i<G[s].size();i++){
        if(G[s][i]==fa){
        	continue;
		}
        dfs(G[s][i],s);
        d[s]+=d[G[s][i]];
        res=max(res,d[G[s][i]]);
    }
    res=max(res,n-d[s]);
    if(res<maxn){
        maxn=res;
        ans=s;
    }
}




//树的中心 
/*
树的中心不一定唯一，但最多有 2
2 个，且这两个中心是相邻的．
树的中心一定位于树的直径上．
树上所有点到其最远点的路径一定交会于树的中心．
当树的中心为根节点时，其到达直径端点的两条链分别为最长链和次长链．
当通过在两棵树间连一条边以合并为一棵树时，连接两棵树的中心可以使新树的直径最小．
树的中心到其他任意节点的距离不超过树直径的一半．
*/
void dfsd(int u,int fa) {
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i],w=edg[i];
		if(v==fa){
		  continue;
		}
		dfsd(v,u);
		if(d1[v]+w>d1[u]){
		  d2[u]=d1[u];
		  d1[u]=d1[v]+w;
		}
		else if(d1[v]+w>d2[u]){
		  d2[u]=d1[v]+w;
		}
	}
}
void dfsu(int u,int fa){
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i],w=edg[i];
		if(v==fa){
		  continue;
		}
		up[v]=up[u]+w;
		if(d1[v]+w!=d1[u]){
		  up[v]=max(up[v],d1[u]+w);
		}
		else{
		  up[v]=max(up[v],d2[u]+w);
		}
		dfsu(v,u);
		}
	}
}
void GetCenter(){
	dfsd(1,0);
	dfsu(1,0);
	for(int i=1;i<=n;i++){
		if(max(d1[i],up[i])<mn){
		  mn=max(d1[i],up[i]);
		  x=i;
		  y=0;
		}
		else if(max(d1[i],up[i])==mn){
		  y=i;
		}
	}
}





//
