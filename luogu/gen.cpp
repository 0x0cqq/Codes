#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 70,K = 1000;
const int MAX = 10000;
int vis[MAX];

int main(){
    srand(time(NULL));
    printf("%d %d\n",n,K);
    memset(vis,0,sizeof(vis));
    for(int i = 1;i<=n;i++){
        int tmp = rand()%MAX;
        while(vis[tmp])
            tmp = rand()%MAX;
        printf("%d ",tmp);
        vis[tmp] = 1;
    }
    putchar('\n');
    memset(vis,0,sizeof(vis));
    for(int i = 1;i<=n;i++){
        int tmp = rand()%MAX;
        while(vis[tmp])
            tmp = rand()%MAX;
        printf("%d ",tmp);
        vis[tmp] = 1;
    }
    putchar('\n');
    memset(vis,0,sizeof(vis));
    for(int i = 1;i<=n;i++){
        int tmp = rand()%MAX;
        while(vis[tmp])
            tmp = rand()%MAX;
        printf("%d ",tmp);
        vis[tmp] = 1;
    }     
    putchar('\n');
    return 0;
}