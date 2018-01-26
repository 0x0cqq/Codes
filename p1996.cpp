#include <cstdio>
using namespace std;

int nex[10000];

int main(){
    int n,m,now;
    scanf("%d %d",&n,&m);
    if(n == 0)
        return 0;
    for(int i = 0;i<n;i++)
        nex[i] = i+1;
    nex[n] = 1;
    now = n;
    while(nex[now]!=now){
        for(int i = 1;i<m;i++)
            now = nex[now];
        printf("%d ",nex[now]);
        nex[now] = nex[nex[now]];
    }
    printf("%d\n",now);
    return 0;
}