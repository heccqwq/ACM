#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N=5e3+5;
const int M=1e4+5;
int d[N],cnt[N]; 
queue<int> q;
int n,m;
int ver[M],hed[N],nxt[M],edg[M],tot; 
void add(int x,int y,int z) {
	ver[++tot]=y;
	nxt[tot]=hed[x];
	hed[x]=tot;
	edg[tot]=z;
}

bool inq[N];
bool spfa(int s)
{
	for(int i=1;i<=n;i++){
		d[i]=1e9;
	}
	q.push(s);
	inq[s]=true;
	cnt[s]++;
	while(q.size())
	{
		int x=q.front();
		q.pop();
		inq[x]=false;
		for(int i=hed[x];i;i=nxt[i])
		{
			int y=ver[i];
			if(d[y]>d[x]+edg[i])
			{
				d[y]=d[x]+edg[i];
				if(!inq[y])
				{
					q.push(y);
					inq[y]=1;
					cnt[y]++;
					if(cnt[y]>n+1){
						return 0;
					}
				}
			}
		}
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		add(0,i,0);
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(y,x,z);
	}
	if(spfa(0)){
		for(int i=1;i<=n;i++){
			cout<<d[i]<<" ";
		}
		return 0;
	}
	printf("NO\n");
}
