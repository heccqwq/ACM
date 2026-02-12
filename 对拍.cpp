#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int main(){
    int testCase=0;
    while(1){
        testCase++;
        cout<<"Running test case #"<<testCase<<"...\n";
        system("data.exe > input.txt");
        system("ac.exe < input.txt > ac.txt");
        system("wa.exe < input.txt > wa.txt");
        int result=system("fc ac.txt wa.txt > nul");
        if(result!=0){
            cout<<"Wrong Answer on test case #"<<testCase<<"!\n";
            cout<<"Input saved in 'wrong_input.txt' "<<endl;
            system("copy input.txt wrong_input.txt");
            break;
        }
        cout<<"Accepted\n\n";
    }
    return 0;
}
