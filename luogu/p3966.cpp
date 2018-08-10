#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <cctype>
#include <cmath>
using namespace std;

const int MAXN = 1001000,logn = 21,MAXM = 300;

namespace SA{
int s[MAXN],sa[MAXN],rk[MAXN],x[MAXN],y[MAXN],ht[MAXN];
int cnt[MAXN];
void get_SA(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]]++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    for(int i = 1;i<n;i++) rk[sa[i]] = s[sa[i]] != s[sa[i-1]]?++m:m;
    for(int j = 1;;j<<=1){
        if(++m == n) break;
        for(int i = 0;i<j;i++) y[i] = n-j+i;
        for(int i = 0,k = j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i]-j;
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
    for(int i = 0,h = ht[0] = 0;i<n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) ++h;
        if(ht[rk[i]] = h) --h;
    }
}
template <typename T>
void build(int n,const T *str){
    int m = 128+200;++n;
    for(int i = 0;i<n;i++)
        s[i] = str[i];
    get_SA(n,m);
    getheight(n);
}
}

namespace ST{
int minn[MAXN][logn];
void build(int n,int *num){
    int l = log2(n);
    for(int i = 0;i<=n;i++)
        minn[i][0] = num[i];
    for(int j = 1;j<=l;j++){
        for(int i = 0;i+(1<<(j-1))<=n;i++){
            minn[i][j] = min(minn[i+(1<<(j-1))][j-1],minn[i][j-1]); 
        }
    }
}
int query(int l,int r){
    int t = log2(r-l+1);
    return min(minn[l][t],minn[r-(1<<t)+1][t]);
}
}

int n,m;

int query(int p,int len){
    p = SA::rk[p];
    int l,r,b = 0,e = p;
    while(b!=e){
        int mid = (b+e)>>1;
        if(ST::query(mid+1,p)<len)
            b = mid+1;
        else e = mid;
    }
    l = b;
    b = p+1,e = n;
    while(b!=e){
        int mid = (b+e)>>1;
        if(ST::query(p+1,mid)>=len) 
            b = mid+1;
        else  e = mid;       
    }
    r = b;
    return r-l;
}

int ans[MAXM];
int b[MAXM],len[MAXM];
int s[MAXN];char t[MAXN];

void init(){
    scanf("%d",&m);
    for(int i = 1;i<=m;i++){
        scanf("%s",t);
        len[i] = strlen(t),b[i] = n;
        for(int j = 0;j<len[i];j++) s[n++] = t[j];
        s[n++] = 127+i;
    }
    s[n] = 'a' - 1;
    SA::build(n,s);
    ST::build(n+1,SA::ht);
}

void solve(){
    for(int i = 1;i<=m;i++){
        printf("%d\n",query(b[i],len[i]));
    }
}

int main(){
    init();
    solve();
    return 0;
}