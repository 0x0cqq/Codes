#include <cstdio>
#include <cstring>
using namespace std;

int n,m;

long long q[1001000];
int w[1001000];
int d[1001000],l[1001000],r[1001000];

int main(){
    scanf("%d %d\n",&n,&m);
    for(int i = 1;i<=n;i++)
        scanf("%d",&w[i]);
    for(int i = 1;i<=m;i++)
        scanf("%d %d %d",&d[i],&l[i],&r[i]);
    int b = 1,e = m+1;
    while(b!=e){
        bool f = 0;
        memset(q,0,sizeof(q));
        int mid = (b+e)>>1;
        for(int i = 1;i<=mid;i++)
            q[l[i]]+=d[i],q[r[i]+1]-=d[i];
        long long tmp = 0;
        for(int i = 1;i<=n;i++){
            tmp+=q[i];
            if(tmp>w[i]){
                f = 1;break;
            }
        }
        if(f)
            e = mid;
        else
            b = mid+1;
    }
    if(b == m+1){
        printf("0\n");
    }
    else{
        printf("-1\n%d\n",b);
    }
    return 0;
}