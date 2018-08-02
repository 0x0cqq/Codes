#include<cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 110000;

int n,m;
struct song{
    int a,b;
    bool operator < (const song &c)const{
        return a-b > c.a-c.b; 
    }
}s[MAXN];

signed main(int argc, char const *argv[]){
    scanf("%lld %lld",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld %lld",&s[i].a,&s[i].b);
    }
    sort(s+1,s+n+1);
    int ans = 0;
    for(int i = 1;i<=n;i++){
        ans += s[i].a;
    }
    if(ans <= m){
        printf("%d\n",0);
        return 0;
    }
    for(int i = 1;i<=n;i++){
        ans -= s[i].a - s[i].b;
        if(ans <= m){
            printf("%lld\n",i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
