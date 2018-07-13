#include <cstdio>
using namespace std;

const int MAXN = 3000100;

int inv[MAXN];
int n,p;

int main(){
    scanf("%d %d",&n,&p);
    inv[1] = 1;
    for(int i = 2;i<=n;i++)
        inv[i] = 1LL*(p-p/i)*inv[p%i]%p;
    for(int i = 1;i<=n;i++)
        printf("%d\n",inv[i]);
    return 0;
}