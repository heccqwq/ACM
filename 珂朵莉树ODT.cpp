#include <bits/stdc++.h>
using namespace std;
map<int,int> s;
int n,m,tot;
void split(int x) {
    if(s.count(x)){
    	return;
	}
    map<int,int>::iterator it=s.lower_bound(x);
    it--; 
    s[x]=it->second;
}
void assign(int l,int r,bool v){
    split(r+1);
    split(l);
    map<int,int>::iterator it=s.find(l);
    while(it->first!=r+1){
        if(it->second==1&&v==0){
            map<int,int>::iterator nxt=it;
            nxt++;
            tot-=(nxt->first-it->first);
        }
        it=s.erase(it);
    }
    s[l]=v;
}
int main() {
    ios::sync_with_stdio(0);
    cin>>n>>m;
    tot=n;
    s[1]=1;
    while(m--){
        int l,r;
        cin>>l>>r;
        assign(l,r,0);
        cout<<tot<<endl;
    }
    return 0;
}

/*
在一条数轴上有 n 个点，分别是 1,2,…,n。
一开始所有的点都被染成黑色。接着我们进行 m 次操作，
第 i 次操作将 [li,ri] 这些点染成白色。请输出每个操作执行后剩余黑色点的个数。
*/
