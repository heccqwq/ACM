#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int inf=0x7fffffff;
int n,tot,root;
struct Treap{
	int l,r;
	int dat,val;
	int size,cnt;
	/*#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define dat(x) tree[x].dat
	#define val(x) tree[x].val
	#define siz(x) tree[x].siz
	#define cnt(x) tree[x].cnt*/
}a[100010];
void Update(int p){
	a[p].size=a[a[p].l].size+a[a[p].r].size+a[p].cnt;
}
int New(int val){
	a[++tot].val=val;
	a[tot].dat=rand();
	a[tot].size=a[tot].cnt=1;
	return tot;
}
void Build(){
	New(-inf);
	New(inf);
	root=1;
	a[1].r=2;
	Update(root);
}
void zig(int &p){
	int q=a[p].l;
	a[p].l=a[q].r;
	a[q].r=p;
	p=q;
	Update(a[p].r);
	Update(p);
}
void zag(int &p){
	int q=a[p].r;
	a[p].r=a[q].l;
	a[q].l=p;
	p=q;
	Update(a[p].l);
	Update(p);
}
void Insert(int &p,int val){
//	cout<<p<<endl;
	if(p==0){
		p=New(val);
	//	cout<<p<<endl;
		return ;
	}
	if(a[p].val==val){
		a[p].cnt++;
		Update(p);
		return ;
	}
	if(val<a[p].val){
		Insert(a[p].l,val);
		if(a[a[p].l].dat>a[p].dat){
			zig(p);
		//	cout<<"r";
		}
	}
	else{
		Insert(a[p].r,val);
		if(a[a[p].r].dat>a[p].dat){
			zag(p);
		//	cout<<"l";
		}
	}
	Update(p);
}
int GetRankByVal(int p,int val){
	if(p==0){
		return 0;
	}
	if(val==a[p].val){
		return a[a[p].l].size+1;
	}
	if(val<a[p].val){
		return GetRankByVal(a[p].l,val);
	}
	return GetRankByVal(a[p].r,val)
		+a[a[p].l].size+a[p].cnt;
}
int GetValByRank(int p,int rank){
	//cout<<p<<"  [  "<<a[p].val<<"   "<<a[p].cnt<<endl;
	if(p==0){
	//	cout<<"ddd";
		return inf;
	}
//	cout<<a[a[p].l].size<<" - "<<p<<endl;
	
	if(a[a[p].l].size>=rank){
	//	cout<<"oooooo";
		return GetValByRank(a[p].l,rank);
	}
	if(a[a[p].l].size+a[p].cnt>=rank){
	//	cout<<"p"<<"  "<<p;
		return a[p].val;
	}
	return GetValByRank(a[p].r,rank-a[a[p].l].size-a[p].cnt);
}
int GetPre(int val){
	int ans=1;
	//cout<<a[1].val<<" -  ";
	int p=root;
	while(p){
	//	cout<<"-"<<p<<"[ "<<a[p].l<<"- "<<a[p].r<<"  [  "<<"  "<<a[p].val<<endl;
		if(a[p].val==val){
			if(a[p].l>0){
				p=a[p].l;
				while(a[p].r>0){
					p=a[p].r;
				}
				ans=p;
			}	
			break;
		}
	//	cout<<p<<endl;
		if(a[p].val>a[ans].val&&a[p].val<val){
			ans=p;
		}
		p=val<a[p].val?a[p].l:a[p].r;
	}
	return a[ans].val;
}
int GetNext(int val){
	int ans=2;
	int p=root;
	while(p){
		if(a[p].val==val){
			if(a[p].r>0){
				p=a[p].r;
				while(a[p].l>0){
					p=a[p].l;
				}
				ans=p;
			}
			break;
		}
		if(a[p].val<a[ans].val&&a[p].val>val){
			ans=p;
		}
		p=val<a[p].val?a[p].l:a[p].r;
	}
	return a[ans].val;
}
void Remove(int &p,int val){
	if(p==0){
		return ;
	}
	if(val==a[p].val){
		if(a[p].cnt>1){
			a[p].cnt--;
			Update(p);
			return ;
		}
		if(a[p].l||a[p].r){
			if(a[p].r==0||a[a[p].l].dat>a[a[p].r].dat){
				zig(p);
				Remove(a[p].r,val);
			}
			else{
				zag(p);
				Remove(a[p].l,val);
			}
			Update(p);
		}
		else{
			p=0;
			return ;
		}
	}
	
	val<a[p].val?Remove(a[p].l,val):Remove(a[p].r,val);
	Update(p);
}
int main(){
	ios::sync_with_stdio(0);
	srand(0);
	Build();
	cin>>n;
	for(int i=1;i<=n;i++){
		int op,x;
		cin>>op>>x;
		if(op==1){
			Insert(root,x);
		}
		if(op==2){
			Remove(root,x);
		}
		if(op==3){
			Insert(root,x);
			cout<<GetRankByVal(root,x)-1<<endl;
			Remove(root,x);
		}
		if(op==4){
			cout<<GetValByRank(root,x+1)<<endl;
		}
		if(op==5){
			cout<<GetPre(x)<<endl;
		}
		if(op==6){
			cout<<GetNext(x)<<endl;
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
