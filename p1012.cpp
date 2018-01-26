#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string x[10000];

bool cmp(string a,string b){
    return a+b>b+a;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        cin>>x[i];
    }
    sort(x,x+n,cmp);
    for(int i = 0;i<n;i++){
        cout<<x[i];
    }
    printf("\n");
    return 0;
}