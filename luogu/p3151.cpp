// Code By Chen Qiqian on 2018.08.10
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

inline int min(int a,int b){
    return a>b?b:a;
}

int n,m;

const int MAXN = 1000100,logn = 20;

namespace SA{
int s[MAXN],sa[MAXN],rk[MAXN],x[MAXN],y[MAXN],ht[MAXN];
int cnt[MAXN];
void get_SA(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]]++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    for(int i = 1;i<n;i++) rk[sa[i]] = (s[sa[i]]!=s[sa[i-1]])?++m:m; 
    for(int j = 1;;j<<=1){
        if(++m == n) break;
        for(int i = 0;i<j;i++) y[i] = n-j+i;
        for(int i = 0,k = j;i<n;i++) if(sa[i]>=j) y[k++] = sa[i]-j;
        for(int i = 0;i<n;i++) x[i] = rk[y[i]];
        for(int i = 0;i<m;i++) cnt[i] = 0;
        for(int i = 0;i<n;i++) cnt[x[i]]++;
        for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
        for(int i = n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
        m = rk[sa[0]] = 0;
        for(int i = 1;i<n;i++) rk[sa[i]] = (y[sa[i]]!=y[sa[i-1]] || y[sa[i]+j]!=y[sa[i-1]+j])?++m:m;
    }
}
void getheight(int n){
    for(int i = 0, h = ht[0] = 0;i<n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) h++;
        if(ht[rk[i]] = h) --h;
    }
}
void build(int n){
    ++n;
    get_SA(n,4);
    getheight(n);
    //QAQ;
}
}
int _log[MAXN];

namespace ST{
int minn[MAXN][logn];
void build(int n,int *num){
    for(int i = 1;i<=n;i++)
        _log[i] = _log[i-1] + ((i==(1<<(_log[i-1]+1)))?1:0);
    int l = _log[n];
    for(int i = 0;i<=n;i++) minn[i][0] = num[i];
    for(int j = 1;j<=l;j++){
        for(int i = 0;i+(1<<(j-1))<=n;i++){
            minn[i][j] = min(minn[i][j-1],minn[i+(1<<(j-1))][j-1]);
        }
    }
}    
int query(int l,int r){
    int t = _log[r-l+1];
    return min(minn[l][t],minn[r-(1<<t)+1][t]);
}
}

int lcp(int x,int y){
    if(x == y) return n-x+1;
    x = SA::rk[x],y = SA::rk[y];
    if(x > y) swap(x,y);
    return ST::query(x+1,y);
}

char s[MAXN];

void init(){
    scanf("%d\n",&m);
    fread(s,MAXN,1,stdin);
    //[0,n)[n,n][n+1,2*n+1)
    // i -> 2*n-i 
    for(int i = 0;i<m;i++) SA::s[n++] = s[i] - ('0'-1);
    reverse(s,s+n);
    SA::s[n++] = 3;
    for(int i = 0;i<m;i++) SA::s[n++] = (s[i]^1) - ('0'-1);
    SA::s[n] = 0;
    // for(int i = 0;i<n;i++)
    //     printf("%d ",t[i]);
    // printf("\n");
    SA::build(n);
    ST::build(n+1,SA::ht);
    // int a,b;
    // while(true){
    //     scanf("%d %d",&a,&b);
    //     printf("%d\n",lcp(a,b));
    // }
}

void solve(){
    long long ans = 0;
    for(int i = 0;i<m;i++){
        // printf("%d %d\n",i+1,n-i-1);
        ans += lcp(i+1,n-i-1);
        // printf("i:%d lcp:%d ANS:%lld\n",i,lcp(i+1,n-i-1),ans);
    }
    printf("%lld\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}