//¸îµã 
void tarjan(int u){
	int fl=0;
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				fl++;
				if(fl>1||u!=root){
					cut[u]=1;
				}
			}
		}
		else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}

//¸î±ß 
void tarjan(int u,int in_edg){
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]){
				bridge[i]=bridge[i^1]=1;
			}
		}
		else if(i!=(in_edg^1)){
			low[u]=min(low[u],dfn[v]);
		}
	}
}

//µãË«Ëõµã 
void tarjan(int x){
	dfn[x]=low[x]=++cnt;
	ins[x]=1;
	s.push(x);
	if(!siz[x]){
		dcc[++cntt].push_back(x);
		return ;
	}
	int ch=0;
	for(int i=hed[x];i;i=nxt[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				ch++;
				if(rt!=x||ch>1){
					cut[x]=1;
				}
				cntt++;
				int z;
				do{
					z=s.top();
					ins[z]=0;
					s.pop();
					dcc[cntt].push_back(z);
				}while(y!=z);
				dcc[cntt].push_back(x);
			}
		}
		else{
			low[x]=min(low[x],dfn[y]);
		}
	}
}
num=cnt;
for(int i=1;i<=n;i++){
	if(cut[i]){
		new_id[i]=++num;
	}
}
tc=1;
for(int i=1;i<=cnt;i++){
	for(int j=0;j<dcc[i].size();j++){
		int x=dcc[i][j];
		if(cut[x]){
			add_c(i,new_id[x]);
			add_c(new_id[x],i);
		}
	}
}

//±ßË«Ëõµã 
void tarjan(int u,int in_edg){
	dfn[u]=low[u]=++cnt;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				brg[i]=brg[i^1]=1;
			}
		}
		else if(i!=(in_edg^1)){
			low[u]=min(low[u],dfn[v]);
		}
	}
}
void dfs(int u){
	vis[u]=1;
	stk[ans].push_back(u);
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(brg[i]||vis[v]){
			continue;
		}
		dfs(v);
	}
}
 
//SCC 
void tarjan(int u){
	low[u]=dfn[u]=++cnt;
	s.push(u),ins[u]=1;
	for(int i=hed[u];i;i=nxt[i]){
		int v=ver[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[u]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		k++;
		do{
			t=s.top();
			s.pop();
			ins[t]=0;
			blgscc[t]=k;
			smscc[k]++;
		}while(t!=u);
	}
}
