#include <cstdio>
using namespace std;

const int MAXN = 10;

int vis[MAXN];

int main(){
    int n;
    scanf("%d",&n);
    char op[20];
    for(int i = 1;i<=n;i++){
        scanf("%s",op);
        if(op[0] == 'p')
            vis[1] = 1;
        if(op[0] == 'g')
            vis[2] = 1;
        if(op[0] == 'b')
            vis[3] = 1;
        if(op[0] == 'o')
            vis[4] = 1;
        if(op[0] == 'r')
            vis[5] = 1;
        if(op[0] == 'y')
            vis[6] = 1;
    }
    int ans = 0;
    for(int i = 1;i<=6;i++){
        if(vis[i] == 0)
            ans++;
    }
    printf("%d\n",ans);
    if(vis[1] == 0)
        printf("Power\n");
    if(vis[2] == 0)
        printf("Time\n");
    if(vis[3] == 0)
        printf("Space\n");
    if(vis[4] == 0)
        printf("Soul\n");
    if(vis[5] == 0)
        printf("Reality\n");
    if(vis[6] == 0)
        printf("Mind\n");
    return 0;
}