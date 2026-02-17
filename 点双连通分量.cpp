#include <bits/stdc++.h>
using namespace std;
int n,m,tot,cntt,cnt,ver[5000050],hed[5000050],nxt[5000050],rt,siz[5000050];
int ins[5000050],low[5000050],dfn[5000050],cut[5000050];
vector<int> vcc[5000050];
stack<int> s;
void add(int a,int b){
	ver[++tot]=b,nxt[tot]=hed[a],hed[a]=tot;
}
void tarjan(int x){
	dfn[x]=low[x]=++cnt;
	ins[x]=1;
	s.push(x);
	if(!siz[x]){
		vcc[++cntt].push_back(x);
		return ;
	}
	int ch=0;
	for(int i=hed[x];i;i=nxt[i]){
		int y=ver[i];
	//	cout<<y<<endl;
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
					vcc[cntt].push_back(z);
				}while(y!=z);
				vcc[cntt].push_back(x);
			}
		}
		else{
			low[x]=min(low[x],dfn[y]);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		if(a==b){
			continue;
		}
		siz[a]++;
		siz[b]++;
		add(a,b);
		add(b,a);
	}
	//cout<<1241<<endl;
	for(int i=1;i<=n;i++){
		//cout<<i;
		rt=i;
		if(!dfn[i]){
			tarjan(i);
		}
	}
	cout<<cntt<<endl;
	for(int i=1;i<=cntt;i++){
		cout<<vcc[i].size()<<" ";
		for(int j=0;j<vcc[i].size();j++){
			cout<<vcc[i][j]<<" ";
		}
		cout<<endl;
	}
}
