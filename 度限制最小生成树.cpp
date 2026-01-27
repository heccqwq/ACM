#include <bits/stdc++.h>
using namespace std;
struct edg{
	int u,v,w;
}e[1000010];
int n,m,s,k,tot,fa[1000010],val[1000010],deg;
vector<int> V;
bool cmp(edg a,edg b){
	return a.w<b.w;
}
int Find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=Find(fa[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>s>>k;
    for(int i=1;i<=n;i++){
    	fa[i]=i;
    	val[i]=1e9;
	}
    for(int i=1;i<=m;i++){
        int u,v,w;
		cin>>u>>v>>w;
        if(u==s){
        	val[v]=min(val[v],w);
        	continue;
		}
        if(v==s){
        	val[u]=min(val[u],w);
        	continue;
		}
        e[++tot]={u,v,w};
    }
    sort(e+1,e+tot+1,cmp);
    long long ans=0;
    for(int i=1;i<=tot;i++){
        int fu=Find(e[i].u),fv=Find(e[i].v);
        if(fu==fv){
        	continue;
		}
        if(val[fu]>val[fv]){
        	swap(fu,fv);
		}
        fa[fv]=fu;
        ans+=e[i].w;
        if(val[fv]!=1e9){
        	V.push_back(val[fv]-e[i].w);
		}
    }
    for(int i=1;i<=n;i++){
        if(Find(i)!=i||i==s){
        	continue;
		}
        if(val[i]==1e9){
			cout<<"Impossible";
			return 0;
		}
        deg++;
        ans+=val[i];
    }
    if(deg>k||deg+V.size()<k){
		cout<<"Impossible";
		return 0;
	}
    sort(V.begin(),V.end());
    for(int i=0;i<k-deg;i++){
    	ans+=V[i];
	}
    cout<<ans<<endl;
    return 0;
}
