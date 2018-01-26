#include <cstdio>
#include <algorithm>
using namespace std;

int k[100000];


int main(){
    int n,m,begin,end;
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
        scanf("%d",k+i);
    scanf("%d",&m);
    sort(k,k+n);
    int b = 0,e = n-1;
    while(e>b+1){
        int t = (b+e)/2;
        if(k[t]>m) e = t;
        else b = t;
    }
    end = e+1;b = 0,e = end-1;
    while(e>b+1){
        int t = (b+e)/2;
        if(k[t]>m/2+1) e = t;
        else b = t;
    }
    begin = b;
    for(int i = 0;i<=begin;i++){
        int temp = m-k[i];
        b = i+1;e = end;
        while(e>b+1){
            int t = (b+e)/2;
            if(k[t]>temp) e = t;
            else b = t;
        }
        if(k[b] == temp||k[e] == temp){
            printf("%d %d\n",k[i],temp);
            return 0;
        }
    }
    printf("No");
    return 0;
}