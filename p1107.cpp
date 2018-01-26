#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string k[1000];

bool cmp(string a,string b){
    for(int i = 0;i<a.size()||i<b.size();i++){
        if(a[i%a.size()]>b[i%b.size()])
            return true;
        else if(a[i%a.size()]<b[i%b.size()])
            return false;
    }
    return true;
}

int main(){
    int n;
    while(scanf("%d",&n)==1){
        for(int i = 0;i<n;i++)
            cin >> k[i];
        sort(k,k+n,cmp);
        for(int i = 0;i<n;i++)
            printf("%s",k[i].c_str());
        printf("\n");
    }
    return 0;
}