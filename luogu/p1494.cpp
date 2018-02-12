#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 51000;

int wazi[MAXN],n,m,times[MAXN],block;

inline int gcd(int a, int b){return b?gcd(b, a%b):a;} 

inline void qr(int &x){
    x = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        x = (x<<3)+(x<<1)+ch-48;
        ch = getchar();
    }
}

struct query{
    int id;
    int l,r;
}q[MAXN],ans[MAXN];

bool cmp(query a,query b){
    int a1= a.l/block,a2 = b.l/block;
    if(a1!=a2){
        return a1<a2;
    }
    else{
        return a1&1? a.r < b.r:a.r > b.r;
    }
}

main(){
    qr(n),qr(m);
    for(int i = 1;i<=n;i++){
        qr(wazi[i]);
    }
    for(int i = 1;i<=m;i++){
        qr(q[i].l),qr(q[i].r);
        q[i].id = i;
    }
    block = sqrt(n)/2;
    sort(q+1,q+m+1,cmp);
    int nowl = 1,nowr = 1,res = 0;
    times[wazi[1]] = 1;
    for(int i = 1;i<=m;i++){
        if(q[i].l == q[i].r){
            ans[q[i].id].l = 0,ans[q[i].id].r = 1;
            continue;
        }
        while(nowl > q[i].l){
            nowl--;
            res += 2 * (times[wazi[nowl]]++);
        }
        while(nowr < q[i].r){
            nowr++;
            res += 2 * (times[wazi[nowr]]++);
        }
        while(nowl < q[i].l){
            res -= 2 * (--times[wazi[nowl]]);
            nowl++;
        }
        while(nowr > q[i].r){
            res -= 2 * (--times[wazi[nowr]]);
            nowr--;
        }
        int x1 = res,x2 = (q[i].r-q[i].l)*(q[i].r-q[i].l+1);
        int g = gcd(x1,x2);
        ans[q[i].id].l = x1/g;ans[q[i].id].r = x2/g;
    }
    for(int i = 1;i<=m;i++){
        printf("%lld/%lld\n",ans[i].l,ans[i].r);
    }
    return 0;
}