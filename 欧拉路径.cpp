#include <bits/stdc++.h>
using namespace std;
int n,m,inedg[1000010],outedg[1000010],s=1,t,hed[1000010];
int cnts,cntt,stk[1000010],top,fl;
vector <int> G[1000010];
void dfs(int now){
	//cout<<now<<endl;
	for(int i=hed[now];i<G[now].size();i=hed[now]){ 
		hed[now]=i+1;
		dfs(G[now][i]);
	}
	stk[++top]=now;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
    for(int i=1;i<=m;i++){
    	int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		outedg[u]++;
		inedg[v]++;  
    }
    for(int i=1;i<=n;i++){
   		sort(G[i].begin(),G[i].end());
	}
    for(int i=1;i<=n;i++){
    	if(outedg[i]!=inedg[i]){
    		fl=1;
		}
        if(outedg[i]-inedg[i]==1){
			s=i;
			cnts++;
        }
        if(inedg[i]-outedg[i]==1){
        	t=i;
			cntt++;
        }
    }
     if(fl&&!(cnts==cntt&&cnts==1)){
		cout<<"No";
		return 0;
    }
  //  cout<<s<<endl;
    dfs(s);
    while(top){
    	cout<<stk[top--]<<" ";
	}
    return 0; 
}
/*
求有向图字典序最小的欧拉路径。
*/
