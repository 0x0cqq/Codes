#include <cstdio>
using namespace std;

int n,m;
bool vis[2000];

int main(){
    scanf("%d %d",&m,&n);
    for(int i = 1;i<=m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        for(int i = l;i<=r;i++){
            vis[i] = 1;
        }
    }
    int cnt = 0;
    for(int i = 1;i<=n;i++){
        if(!vis[i]) cnt++;
    }
    printf("%d\n",cnt);
    for(int i =  1;i<=n;i++){
        if(!vis[i])
            printf("%d ",i);
    }
    printf("\n");
    return 0;
}