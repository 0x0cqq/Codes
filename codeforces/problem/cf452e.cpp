#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 1e9+7;

const int MAXN = 340000;

namespace SA{
  int s[MAXN],sa[MAXN],cnt[MAXN],rk[MAXN],x[MAXN],y[MAXN],ht[MAXN];
  void get_sa(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]]++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i=n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    for(int i = 1;i<n;i++) rk[sa[i]] = s[sa[i]] == s[sa[i-1]]?m:++m;
    for(int j = 1;;j<<=1){
      if(++m == n) break;
      for(int i = 0;i<j;i++) y[i] = n-j+i;
      for(int i=0,k=j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i]-j; 
      for(int i = 0;i<n;i++) x[i] = rk[y[i]];
      for(int i = 0;i<m;i++) cnt[i] = 0;
      for(int i = 0;i<n;i++) cnt[x[i]]++;
      for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
      for(int i =n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
      m = rk[sa[0]] = 0;
      for(int i = 1;i<n;i++) rk[sa[i]] = 
        (y[sa[i]] == y[sa[i-1]] && y[sa[i]+j] == y[sa[i-1]+j])?m:++m;
    } 
  }
  void getheight(int n){
    for(int i = 0,h = ht[0] = 0;i<n;i++){
      int j = sa[rk[i]-1];
      while(i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
      ht[rk[i]] = h;
      if(h) h--;
    }
  }
  void solve(int *str,int n){
    for(int i = 0;i<n;i++) s[i] = str[i];
    get_sa(++n,200);
    getheight(n);
    // printf("s:\n");
    // for(int i = 0;i<n;i++) printf("%d ",s[i]);
    // printf("\n");
    // printf("sa:\n");
    // for(int i = 0;i<n;i++) printf("%d ",sa[i]);
    // printf("\n");
    // printf("ht:\n");
    // for(int i = 0;i<n;i++) printf("%d ",ht[i]);
    // printf("\n");
  }
}

ll ANS = 0,ans[MAXN];

namespace BCJ{
  int f[MAXN],num[MAXN][4];
  void init(int n,int *own){
    for(int i = 0;i<=n;i++)
      f[i] = i,num[i][own[i]] = 1;
  }
  int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
  }
  int cal(int x){
    return 1LL * num[x][1] * num[x][2] * num[x][3] % mod;
  }
  void merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    ANS -= cal(fx),ANS -= cal(fy);
    f[fx] = fy;
    for(int i = 1;i<=3;i++) num[fy][i] += num[fx][i];
    ANS += cal(fy);
    ANS = (ANS%mod);
    if(ANS < 0) ANS += mod;
  }
}

int ss;
int S[MAXN];
int own[MAXN];

void addchar(int c,int x = 0){own[ss] = x;S[ss] = c;ss++;} 
int l1,l2,l3;
char s1[MAXN],s2[MAXN],s3[MAXN];
void init(){
  scanf("%s",s1);l1 = strlen(s1);
  scanf("%s",s2);l2 = strlen(s2);
  scanf("%s",s3);l3 = strlen(s3);
  for(int i = 0;i<l1;i++) addchar(s1[i],1);
  addchar('z'+1);
  for(int i = 0;i<l2;i++) addchar(s2[i],2);
  addchar('z'+2);
  for(int i = 0;i<l3;i++) addchar(s3[i],3);
  addchar('z'+3);
}

struct Node{
  int pos,v;
  bool operator < (const Node &x)const{
    return v > x.v;
  }
};

vector<Node> v;

void solve(){
  BCJ::init(ss+1,own);
  SA::solve(S,ss);
  for(int i = 1;i<ss+1;i++){
    v.push_back((Node){i,SA::ht[i]});
  }
  sort(v.begin(),v.end());
  int now = 0;
  int t = min(l1,min(l2,l3));
  for(int i = t;i>=1;--i){
    while(now < int(v.size())-1 && v[now].v >= i){
      int tmp = v[now].pos;
      BCJ::merge(SA::sa[tmp],SA::sa[tmp-1]);
      now++;
    }
    ans[i] = ANS;
  }
  for(int i = 1;i<=t;i++){
    printf("%lld ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}