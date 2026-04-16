#include <bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,root,tot;
struct splay{
	int ch[3],val,cnt;
	int size,fa;
}a[1000010];
void Update(int p){
	a[p].size=a[a[p].ch[0]].size+a[a[p].ch[1]].size+a[p].cnt;
}
void Rotate(int x){
	int y=a[x].fa;
	int z=a[y].fa;
	int kid=a[y].ch[1]==x;
	a[z].ch[a[z].ch[1]==y]=x;
	a[x].fa=z;
	a[y].ch[kid]=a[x].ch[kid^1];
	a[a[x].ch[kid^1]].fa=y;
	a[x].ch[kid^1]=y;
	a[y].fa=x;
	Update(y);
	Update(x);
}
void Splay(int x,int goal){
	while(a[x].fa!=goal){
		int y=a[x].fa;
		int z=a[y].fa;
		if(z!=goal){
			(a[z].ch[1]==y)^(a[y].ch[1]==x)?Rotate(x):Rotate(y);
		}
		Rotate(x);
	}
	if(goal==0){
		root=x;
	}
}
void Insert(int val){
	int now=root,fa=0;
	while(now&&a[now].val!=val){
		fa=now;
		now=a[now].ch[a[now].val<val];
	}
	if(now){
		a[now].cnt++;
	}
	else{
		now=++tot;
		if(fa){
			a[fa].ch[a[fa].val<val]=now;
			a[now].fa=fa;
		}
		a[now].val=val;
		a[now].size=a[now].cnt=1;
	}
	Splay(now,0);
}
void Search(int val){
	int now=root;
	if(!now){
		return ;
	}
	while(a[now].val!=val&&a[now].ch[a[now].val<val]){
		now=a[now].ch[a[now].val<val];
	}
	Splay(now,0);
}
int GetValByRank(int p,int rank){
	if(!p){
		return 0;
	}
	if(a[a[p].ch[0]].size>=rank){
		return GetValByRank(a[p].ch[0],rank);
	}
	if(a[a[p].ch[0]].size+a[p].cnt>=rank){
		return a[p].val;
	}
	return GetValByRank(a[p].ch[1],rank-a[a[p].ch[0]].size-a[p].cnt);
	
}
int GetPre(int val){
	Search(val);
	int pos=a[root].ch[0];
	while(a[pos].ch[1]){
		pos=a[pos].ch[1];
	}
	return pos;
}
int GetNext(int val){
	Search(val);
	int pos=a[root].ch[1];
	while(a[pos].ch[0]){
		pos=a[pos].ch[0];
	}
	return pos;
}
void Remove(int x){
	int pre_x=GetPre(x);
	int nxt_x=GetNext(x);
	Splay(pre_x,0);
	Splay(nxt_x,pre_x);
	int pos=a[root].ch[1];
	if(a[a[pos].ch[0]].cnt>1){
		a[a[pos].ch[0]].cnt--;
		Update(nxt_x);
		Update(pre_x);
		Splay(a[pos].ch[0],0);
		return ;
	}
	a[pos].ch[0]=0;
	Update(nxt_x);
	Update(pre_x);
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	Insert(-inf);
	Insert(inf);
	for(int i=1;i<=n;i++){
		int opt,x;
		cin>>opt>>x;
		if(opt==1){
			Insert(x);
		}
		if(opt==2){
			Remove(x);
		}
		if(opt==3){
			Insert(x);
			Search(x);
			cout<<a[a[root].ch[0]].size<<endl;
			Remove(x);
		}
		if(opt==4){
			cout<<GetValByRank(root,x+1)<<endl;
		}
		if(opt==5){
			Insert(x);
			cout<<a[GetPre(x)].val<<endl;
			Remove(x);
		}
		if(opt==6){
			Insert(x);
			cout<<a[GetNext(x)].val<<endl;
			Remove(x);
		}
	}
}
/*
您需要动态地维护一个可重集合 M，并且提供以下操作：

向 M 中插入一个数 x。
从 M 中删除一个数 x（若有多个相同的数，应只删除一个）。
查询 M 中有多少个数比 x 小，并且将得到的答案加一。
查询如果将 M 从小到大排列后，排名位于第 x 位的数。
查询 M 中 x 的前驱（前驱定义为小于 x，且最大的数）。
查询 M 中 x 的后继（后继定义为大于 x，且最小的数）。
对于操作 3,5,6，不保证当前可重集中存在数 x。

对于操作 5,6，保证答案一定存在。

输入格式
第一行为 n，表示操作的个数，下面 n 行每行有两个数 opt 和 x，opt 表示操作的序号（1≤opt≤6）。

输出格式
对于操作 3,4,5,6 每行输出一个数，表示对应答案。
*/
