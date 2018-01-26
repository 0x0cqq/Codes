#include <cstdio>
#include <cstring>
using namespace std;

bool p[10000010];

void prime(int k){
    memset(p,1,k+1);
    p[1] = 0;
    for(int i = 2;i<=(k+1)/2;i++)
        if(p[i]){
            int t = 2*i;
            while(t<=k+1){
                p[t] = 0;
                t+=i;
            }
        }
}


int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    prime(n);
    for(int i = 0;i<m;i++){
        int t;
        scanf("%d",&t);
        if(p[t])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}