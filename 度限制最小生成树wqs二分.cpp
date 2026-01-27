#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e12;
int n,m,s,k,tot0,tot1,fa[1000010],cnt,res;
struct edg{
    int u,v,w;
    bool isNeed;
}orig[2][1000010],e[1000010];
bool cmp(edg a,edg b){
    return a.w<b.w;
}
int Find(int x){
    if(fa[x]==x){
    	return x;
	}
    return fa[x]=Find(fa[x]);
}
bool Merge(int u,int v){
    int fu=Find(u),fv=Find(v);
    if(fu==fv){
    	return 0;
	}
    fa[fu]=fv;
    return 1;
}
void mergeSort(int delta){
    for(int i=1;i<=tot1;i++){
    	orig[1][i].w+=delta;
	}
    int i=1,j=1,sm=0;
    while(i<=tot0&&j<=tot1){
        if(orig[0][i].w<orig[1][j].w){
        	e[++sm]=orig[0][i++];
        	continue;
		}
        e[++sm]=orig[1][j++];
    }
    while(i<=tot0){
    	e[++sm]=orig[0][i++];
	}
    while(j<=tot1){
    	e[++sm]=orig[1][j++];
	}
    for(int i=1;i<=tot1;i++){
    	orig[1][i].w-=delta;
	}
}
bool check(int delta){
    mergeSort(delta);
    res=0,cnt=0;
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
    int block=n;
    for(int i=1;i<=m;i++){
        if(!Merge(e[i].u,e[i].v)){
        	continue;
		}
        cnt+=e[i].isNeed;
        res+=e[i].w;
        block--;
        if(block==1){
        	break;
		}
    }
    if(cnt>=k){
    	return 1;
	}
	return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>s>>k;
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(u==s||v==s){
            orig[1][++tot1]={u,v,w,1};
            continue;
        }
        orig[0][++tot0]={u,v,w,0};
    }
    if(tot1<k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    int block=n;
    for(int i=1;i<=tot0;i++){
    	if(Merge(orig[0][i].u,orig[0][i].v)){
    		block--;
		}
	}
    for(int i=1;i<=tot1;i++){
    	if(Merge(orig[1][i].u,orig[1][i].v)){
    		block--;
		}
	}
    if(block!=1){
        cout<<"Impossible"<<endl;
        return 0;
    }
    sort(orig[0]+1,orig[0]+tot0+1,cmp);
    sort(orig[1]+1,orig[1]+tot1+1,cmp);
    if(!check(-inf)||cnt<k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    check(inf);
    if(cnt>k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    int l=-inf,r=inf,maxp=-inf;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            maxp=mid;
            l=mid+1;
            continue;
        }
        r=mid-1;
    }
    check(maxp);
    cout<<res-maxp*k<<endl;
    return 0;
}
