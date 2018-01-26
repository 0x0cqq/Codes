#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

string k[100];

int main(){
    int n,maxn;
    size_t max = 0;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        cin>>k[i];
    for(int i = 1;i<=n;i++){
        //printf(":%lu %lu\n",k[i].size(),max);
        if(k[i].size()>max){
            max = k[i].size();
            maxn = i;
            //printf("::");
        }else if(k[i].size()==max){
            if(k[maxn]<k[i])
                maxn = i;
        }
    }
    printf("%d\n",maxn);
    printf("%s\n",k[maxn].c_str());
    return 0;
}