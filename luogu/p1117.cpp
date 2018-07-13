#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

struct SA{
int sa[MAXN],rk[MAXN],ht[MAXN],s[MAXN<<1],t[MAXN<<1];
int b[MAXN],cur[MAXN],p[MAXN];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) \
    fill_n(b,m,0),fill_n(sa,n,-1);\
    for(int i = 0;i<n;i++) b[s[i]]++;\
    for(int j = 1;j<m;j++) b[j]+=b[j-1];\
    for(int j = 0;j<m;j++) cur[j] = b[j]-1;\
    for(int i=n1-1;~i;--i) pushS(v[i]);\
    for(int j = 1;j<m;j++) cur[j] = b[j-1];\
    for(int i = 0;i<n;i++) if(sa[i]>0 && t[sa[i]-1]) pushL(sa[i]-1);\
    for(int j = 0;j<m;j++) cur[j] = b[j]-1;\
    for(int i=n-1;~i;--i) if(sa[i]>0 && !t[sa[i]-1]) pushS(sa[i]-1);

void sais(int n,int m,int *s,int *t,int *p){
    int n1 = t[n-1] = 0,ch = rk[0] = -1,*s1 = s+n;
    for(int i = n-2;~i;--i) t[i] = (s[i]!=s[i+1])?s[i]>s[i+1]:t[i+1];
    for(int i = 1;i<n;i++) rk[i] = (!t[i]&&t[i-1])?(p[n1]=i,n1++):-1;
    inducedSort(p);
    for(int i=0,x,y;i<n;i++)if(~(x=rk[sa[i]])){
        if(ch < 1 || p[x+1]-p[x]!=p[y+1]-p[y]) ch++;
        else for(int j=p[x],k=p[y];j<=p[x+1];j++,k++)
            if((s[j]<<1|t[j])!=(s[k]<<1|t[k])){ch++;break;}
        s1[y=x]=ch;
    }
    if(ch+1 < n1) sais(n1,ch+1,s1,t+n,p+n1);
    else for(int i = 0;i<n1;i++) sa[s1[i]] = i;
    for(int i = 0;i<n1;i++) s1[i] = p[sa[i]];
    inducedSort(s1);
}
template<typename T>
int mapp(const T *str,int n){
    int m = *max_element(str,str+n);
    fill_n(rk,m+1,0);
    for(int i = 0;i<n;i++) rk[str[i]] = 1;
    for(int j = 0;j<m;j++) rk[j+1] += rk[j];
    for(int i = 0;i<n;i++) s[i] = rk[str[i]] - 1;
    return rk[m];
}
template<typename T>
void SuffixArray(const T *str,int n){
    int m = mapp(str,++n);
    sais(n,m,s,t,p);
}
void getheight(int n){
    for(int i = 0;i<=n;i++) rk[sa[i]] = i;
    for(int i = 0,h = ht[0] = 0;i<=n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) h++;
        if(ht[rk[i]] = h) --h;
    }
}
struct ST{
    int maxn[20][MAXN];
    void build(int *num,int n){
        for(int i = 1;i<=n;i++) maxn[0][i] = num[i];
        // st表取min！
        for(int j = 1,t=2;t<=n;j++,t<<=1)
            for(int i = 1;i+(t>>1)<=n;i++)
                maxn[j][i] = min(maxn[j-1][i],maxn[j-1][i+(t>>1)]);
    }
    int query(int l,int r){
        if(l > r) return -1;
        int t = log2(r-l+1);
        // 取min！！！！
        return min(maxn[t][l],maxn[t][r-(1<<t)+1]);
    }
}S;
int lcp(int x,int y,int n){
    // printf("lcp:%d %d\n",x,y);
    x = rk[x],y = rk[y];
    if(x > y) swap(x,y);
    if(x == y) return n-x+1;
    return S.query(x+1,y);
}
template<typename T>
void solve(const T *str,int n){
    SuffixArray(str,n);
    getheight(n);
    S.build(ht,n);
}
}A,B;

int n;
char s[MAXN],tmp[MAXN];

void init(){
    scanf("%s",s);
    n = strlen(s);
    s[n] = 'a'-1;
    A.solve(s,n);
    for(int i = 0;i<n;i++) tmp[i] = s[n-i-1];
    tmp[n] = 'a'-1;
    B.solve(tmp,n);
}
// Longest Common Prefix
int lcp(int x,int y){
    return A.lcp(x,y,n);
}
// Longest Common Suffix
int lcs(int x,int y){
    return B.lcp(n-x-1,n-y-1,n);
}

long long solve(){
    static long long l[MAXN],r[MAXN];
    long long ans = 0;
    memset(l,0,sizeof(l)),memset(r,0,sizeof(r));
    for(int L = 1;L<=n/2;L++){
        for(int j = 0;j+L<n;j+=L){
            int ll = j,rr = j+L;
            if(s[ll] != s[rr]) continue;
            int x = ll-lcs(ll,rr)+1,y = ll + lcp(ll,rr) - 1;
            x = max(max(x,0),ll-L+1),y = min(ll+L-1,min(n-L-1,y));
            if(y-x+1 >= L){
                int cnt = (y-x+1)-L+1;
                l[x]++,l[x+cnt]--;
                r[x+2*L-1]++,r[x+2*L+cnt-1]--;
            }
        }
    }

    for(int i = 1;i<n;i++) l[i] += l[i-1],r[i] += r[i-1];
    for(int i = 0;i<n-1;i++) ans += r[i]*l[i+1];
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        init();
        printf("%lld\n",solve());
    }
    return 0;
}