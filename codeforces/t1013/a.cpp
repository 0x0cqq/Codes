#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100;

int n;
int x[MAXN],y[MAXN];

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&x[i]);
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&y[i]);
    }
    bool flag = 1;
    int ans = 0;
    for(int i = 1;i<=n;i++){
        ans += x[i];
        ans -= y[i];
    }
    if(ans >= 0)
        printf("Yes\n");
    else
        printf("No\n");
}