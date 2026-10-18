#include <bits/stdc++.h>
using namespace std;
int ans[4][4]={{0,0,0,0},{0,1,2,3},{0,8,0,4},{0,7,6,5}},a[5][5],k,fl;
string ss;
int dx[6]={0,1,-1,0},dy[6]={1,0,0,-1};
int check(){
    for(int i=1;i<=3;i++){
    	for(int j=1;j<=3;j++){
    		if(ans[i][j]!=a[i][j]){
    			return 0;
			}
		}
	}
    return 1;
}
int test(int step){
    int cnt=0;
    for(int i=1;i<=3;i++){
    	for(int j=1;j<=3;j++){
    		if(ans[i][j]!=a[i][j]){
    			cnt++;
				if(cnt+step>k){
					return 0;
				}
			}
    	}
    }
    return 1;
}
void A_star(int step,int x,int y,int pre){
    if(step==k){
		if(check()){
			fl=1;
		}
		return ;
	}
    if(fl){
    	return;
	}
    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<1||nx>3||ny<1||ny>3||pre+i==3){
        	continue;
		}
        swap(a[x][y],a[nx][ny]);
        if(test(step)&&(!fl)){
			A_star(step+1,nx,ny,i);
		}
        swap(a[x][y],a[nx][ny]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin>>ss;
    int x,y;
    for(int i=0;i<9;i++){
        a[i/3+1][i%3+1]=ss[i]-'0';
        if(ss[i]-'0'==0){
        	x=i/3+1;
			y=i%3+1;
		}
    }
    if(check()){
		cout<<0;
		return 0;
	}
    while(++k){
        A_star(0,x,y,-1);
        if(fl){
			cout<<k<<endl;
			break;
		}
    }
    return 0;
}
/*
在 3×3 的棋盘上，摆有八个棋子，每个棋子上标有 1 至 8 的某一数字。
棋盘中留有一个空格，空格用 0 来表示。空格周围的棋子可以移到空格中。
要求解的问题是：给出一种初始布局,设目标状态为 123804765）
找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。
*/
