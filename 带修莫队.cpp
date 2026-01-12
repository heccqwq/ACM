#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000010],cnt_Q,cnt_R,cnt[1000010];
int l=1,r,t,sm,size,ans[1000010];
struct Q{
	int l,r,time,id;
}q[1000010];
struct C{
	int col,pos;
}c[100010];
bool operator<(Q a,Q b){
	if(a.l/size==b.l/size){
		if(a.r/size==b.r/size){
			return a.time<b.time;
		}
		return a.r<b.r;
	}
	return a.l/size<b.l/size;
}
void Add(int p){
	cnt[a[p]]++;
	if(cnt[a[p]]==1){
		sm++;
	}
}
void Del(int p){
	cnt[a[p]]--;
	if(cnt[a[p]]==0){
		sm--;
	}
}
signed main(){
	cin>>n>>m;
	size=pow(n,0.666);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		char a;
		int x,y;
		cin>>a>>x>>y;
		if(a=='Q'){
			cnt_Q++;
			q[cnt_Q].l=x;
			q[cnt_Q].r=y;
			q[cnt_Q].id=cnt_Q;
			q[cnt_Q].time=cnt_R;
		}
		if(a=='R'){
			cnt_R++;
			c[cnt_R].pos=x;
			c[cnt_R].col=y;
		}
	}
	sort(q+1,q+cnt_Q+1);
	for(int i=1;i<=cnt_Q;i++){
		while(l<q[i].l){
			Del(l++);
		}
		while(l>q[i].l){
			Add(--l);
		}
		while(r<q[i].r){
			Add(++r);
		}
		while(r>q[i].r){
			Del(r--);
		}
		while(t<q[i].time){
			t++;
			if(c[t].pos>=q[i].l&&c[t].pos<=q[i].r){
				cnt[a[c[t].pos]]--;
				cnt[c[t].col]++;
				if(cnt[a[c[t].pos]]==0){
					sm--;
				}
				if(cnt[c[t].col]==1){
					sm++;
				}	
			}
			swap(a[c[t].pos],c[t].col);
		}
		while(t>q[i].time){
			if(c[t].pos>=q[i].l&&c[t].pos<=q[i].r){
				cnt[a[c[t].pos]]--;
				cnt[c[t].col]++;
				if(cnt[a[c[t].pos]]==0){
					sm--;
				}
				if(cnt[c[t].col]==1){
					sm++;
				}
			}
			swap(a[c[t].pos],c[t].col);
			t--;
		}
		ans[q[i].id]=sm;
	}
	for(int i=1;i<=cnt_Q;i++){
		cout<<ans[i]<<endl;
	}
}
/*
墨墨购买了一套 N 支彩色画笔（其中有些颜色可能相同），摆成一排，你需要回答墨墨的提问。墨墨会向你发布如下指令：

Q L R 代表询问你从第 L 支画笔到第 R 支画笔中共有几种不同颜色的画笔。

R P C 把第 P 支画笔替换为颜色 C。

为了满足墨墨的要求，你知道你需要干什么了吗？

输入格式
第 1 行两个整数 N，M，分别代表初始画笔的数量以及墨墨会做的事情的个数。

第 2 行 N 个整数，分别代表初始画笔排中第 i 支画笔的颜色。

第 3 行到第 2+M 行，每行分别代表墨墨会做的一件事情，格式见题干部分。

输出格式
对于每一个 Query 的询问，你需要在对应的行中给出一个数字，代表第 L 支画笔到第 R 支画笔中共有几种不同颜色的画笔。
*/
