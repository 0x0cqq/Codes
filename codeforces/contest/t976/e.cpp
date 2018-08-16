#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1000000;

struct q{
    int x,y;
}p[MAXN];

bool cmp(q a,q b){
    return a.x - a.y > b.x - b.y;
}

int n,a,b;

main(){
    scanf("%lld %lld %lld",&n,&a,&b);
    int tmp = pow(2,a);
    for(int i = 1;i<=n;i++){
        scanf("%lld %lld",&p[i].x,&p[i].y);
    }
    sort(p+1,p+n+1,cmp);
    int ans = 0,sss = 0;
    int x = n;
    for(int i = 1;i<=n;i++){
        if(p[i].y > p[i].x){
            x = i-1;
            break;
        }
    }
    if(x < b)
        b = x;
    for(int i = 1;i<=b;i++) ans += p[i].x;
    for(int i = b+1;i<=n;i++) ans += p[i].y;
    if(a == 0 && b == 0){
        printf("%lld\n",ans);
        return 0;
    } 
    if(x == b){
        for(int i = 1;i<=b;i++)
            sss = max(ans - p[i].x + tmp * p[i].x,sss);
        for(int i = b+1;i<=n;i++){
            sss = max(ans - p[i].y + tmp * p[i].x - p[b].x + p[b].y,sss);
        }
    }
    else {
        for(int i = 1;i<=b;i++){
            sss = max(ans-p[i].x + tmp * p[i].x,sss);
        }
        for(int i = b+1;i<=n;i++)
            sss = max(ans - p[i].y + tmp * p[i].x - p[b].x + p[b].y,sss);
    }
    printf("%lld\n",sss);
    return 0;
}