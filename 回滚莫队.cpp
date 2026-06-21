#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,a[1000010],b[1000010],block[1000010],R[1000010],ans[1000010];
int bl,mx[1000010],mn[1000010];
struct Que{
	int l,r,id;
}q[1000010];
bool cmp(Que a,Que b){
	if(block[a.l]==block[b.l]){
		return a.r<b.r;
	}
	return block[a.l]<block[b.l];
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	int M=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+M,a[i])-b;
	}
	int bl=sqrt(n);
	for(int i=1;i<=n;i++){
		block[i]=(i-1)/bl+1;
	}
	for(int i=1;i<=bl+1;i++){
		R[i]=min(i*bl,n);
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	int l=0,r=0,lst=0,tmp=0;
	for(int i=1;i<=m;i++){
		if(block[q[i].l]==block[q[i].r]){
			tmp=0;
			for(int j=q[i].r;j>=q[i].l;j--){
				mx[a[j]]=mn[a[j]]=0;
			}
			for(int j=q[i].r;j>=q[i].l;j--){
				if(!mx[a[j]]){
					mx[a[j]]=j;
					continue;
				}
				tmp=max(tmp,mx[a[j]]-j);
			}
			for(int j=q[i].r;j>=q[i].l;j--){
				mx[a[j]]=mn[a[j]]=0;
			}
			ans[q[i].id]=tmp;
			continue;
		}
		if(lst!=block[q[i].l]){
			while(r>R[block[q[i].l]]){
				mx[a[r]]=mn[a[r]]=0;
				r--;
			}
			while(l<R[block[q[i].l]]+1){
				mx[a[l]]=mn[a[l]]=0;
				l++;
			}
			r=l-1;
			lst=block[q[i].l];
			tmp=0;
		}
		while(r<q[i].r){
			r++;
			if(!mn[a[r]]){
				mn[a[r]]=mx[a[r]]=r;
				continue;
			}
			mx[a[r]]=r;
			tmp=max(tmp,r-mn[a[r]]);
		}
		int ll=l,res=tmp;
		while(ll>q[i].l){
			ll--;
			if(!mx[a[ll]]){
				mx[a[ll]]=ll;
				continue;
			}
			res=max(res,mx[a[ll]]-ll);
		}
		ans[q[i].id]=res;
		while(ll<l){
			if(mx[a[ll]]==ll){
				mx[a[ll]]=0;
			}
			ll++;
		}
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}

/*
给定一个序列，多次询问一段区间 [l,r]，求区间中相同的数的最远间隔距离。

序列中两个元素的间隔距离指的是两个元素下标差的绝对值。
*/

