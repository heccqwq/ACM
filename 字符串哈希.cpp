#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
unsigned long long a[10010],base=131,ans,n,md=314931493149,sm=314931;
char s[10010];
unsigned long long hashr(char a[]){
	unsigned long long x=0;
	for(int j=0;j<strlen(a);j++){
	    x=(x*base+(unsigned long long)a[j])%md+sm;
	}
	return x;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
      //  int len=strlen(s);
        a[i]=hashr(s);
		/*for(int j=0;j<len;j++)
		{
			a[i]=(a[i]*base+(unsigned long long)s[j]);
		}*/
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]){
			ans++;
		}
	}
	cout<<ans;
}
