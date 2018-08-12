#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 1110;

int p[MAXN];
bool vis[MAXN];

int n;
int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&p[i]);
    }
    for(int i = 1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        int nown = i;
        while(vis[nown] == 0){
            vis[nown] = 1;
            nown = p[nown];
        }
        printf("%d ",nown);
    }
    printf("\n");
    return 0;
}
