#include<bits/stdc++.h>
using namespace std;
int n, ans;
char s[20000010];

int main(){
    cin >> n >> (s + 1);
    for(int i = 1; i <= n; i++){
        s[n + i] = s[i];
    }
    int i = 1, j = 2, k;
    while(i <= n && j <= n){
        for(k = 0; k < n && s[i+k] == s[j+k]; k++) ;
        if(k == n){
            break;
        }
        if(s[i+k] > s[j+k]){
            i = i + k + 1;
            if(i == j){
                i++;
            }
        } else {
            j = j + k + 1;
            if(i == j){
                j++;
            }
        }
    }
    ans = min(i, j);
    for(int i = 0; i < n; i++){
        cout << s[i + ans];
    }
}
