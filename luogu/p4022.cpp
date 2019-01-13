#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100000;

namespace SAM{
  int c[MAXN][2],l[MAXN],fa[MAXN],cnt,last,rt;
  void init(){rt = last = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  int ins(int p,int x){
    if(c[p][x]){
      int q = c[p][x];
      if(l[q] == l[p] + 1) last = q;
      else{
        int nq = newnode(l[p]+1);last = nq;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    else{
      int np = newnode(l[p]+1);last = np;
      for(;p && (!c[p][x]);p = fa[p]) c[p][x] = np;
      if(!p) fa[np] = rt;
      else{
        int q = c[p][x];
        if(l[q] == l[p]+1) fa[np] = q;
        else{
          int nq = newnode(l[p]+1);
          memcpy(c[nq],c[q],sizeof(c[q]));
          fa[nq] = fa[q];fa[q] = fa[np] = nq;
          for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
        }
      }
    }
    return last;
  }
  void ins(char *s){
    int n = strlen(s),p = rt;
    for(int i = 0;i<n;i++) p = ins(p,s[i]-'0');
  }
  void calmax(int n,char *s,int *res){
    int now = rt,cur = 0;
    for(int i = 0;i<n;i++){
      int x = s[i] - '0';
      if(c[now][x]){
        cur++,now = c[now][x];
      }
      else{
        while(now && !c[now][x]) now = fa[now];
        if(now == 0) now = rt,cur = 0;
        else cur = l[now] + 1,now = c[now][x];
      }
      res[i+1] = cur;
    }
  }
}

int n,m;
char s[MAXN];
int maxlen[MAXN];
int dp[MAXN];
int q[MAXN],fi,la;

bool check(int n,int L){// 长度为 L 的情况下是否可以实现
  fi = 0,la = -1;
  for(int i = 0;i < L;i++) dp[i] = 0;
  for(int i = L;i <= n;i++){
    // printf("%d:%d\n",i,maxlen[i]);
    dp[i] = dp[i-1];
    while(fi <= la && dp[q[la]] + (i-q[la]) <= dp[i-L] + (i-(i-L))) la--;
    q[++la] = i-L;
    while(fi <= la && q[fi] < i - maxlen[i]) fi++;
    if(fi <= la)
      dp[i] = max(dp[i],dp[q[fi]] + (i-q[fi]));
  }
  // printf("%d\n",dp[n]);
  return dp[n] * 10 >= n * 9;
}


int cal(char *s){
  int n = strlen(s);
  SAM::calmax(n,s,maxlen);
  int L = 1,R = 1000000;
  while(L != R){
    int mid = (L+R+1)/2;
    if(!check(n,mid)){
      R = mid-1;
    }
    else{
      L = mid;
    }
  }
  return L;
}


void init(){
  scanf("%d %d",&n,&m); 
  SAM::init();
  for(int i = 1;i <= m;i++){
    scanf("%s",s);
    SAM::ins(s);
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    scanf("%s",s);
    printf("%d\n",cal(s));
  }
}

int main(){
  init();
  solve();
  return 0;
}