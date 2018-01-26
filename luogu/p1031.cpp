#include <cstdio>
using namespace std;

int k[1000];

int main(){
    int n;
    scanf("%d",&n);
    int ans = 0;
    for(int i = 0;i<n;i++){
        scanf("%d",k+i);
        ans+=k[i];
    }
    ans/=n;
    int res = 0;
    for(int i = 0;i<n-1;i++){
        if(k[i]!=ans){
            k[i+1]-=(ans-k[i]);
            res++;
        }
    }
    printf("%d\n",res);
    return 0;
}