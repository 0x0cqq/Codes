#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

struct PAM{
  int s[MAXN],c[MAXN][26],fa[MAXN],len[MAXN],tcnt,last;
  void init(){
    s[0] = -1;
    last = 0,tcnt = 1;
    fa[0] = fa[1] = 1;
    len[0] = 0,len[1] = -1; 
  }
  int getfail(int n,int p){
    while(s[n-len[p]-1] != s[n]) p = fa[p];
    return p;
  }
  int ins(int n,int x){// 返回最长回文后缀长度
    s[n] = x;
    int p = getfail(n,last),&q = c[p][x];
    if(!q){
      int f = c[getfail(n,fa[p])][x];
      q = ++tcnt,len[q] = len[p]+2,fa[q] = f;
    }
    last = q;
    return len[q];
  }
}A,B;

int n;char s[MAXN];
int a[MAXN],b[MAXN];

int main(){
  scanf("%s",s+1);n = strlen(s+1);
  A.init(),B.init();
  for(int i = 1;i<=n;i++) a[i] = A.ins(i,s[i]-'a');//,printf("%d:%d\n",i,a[i]);
  for(int i = n;i>=1;--i) b[i] = B.ins(n-i+1,s[i]-'a');//,printf("%d:%d\n",i,b[i]);
  int ans = 0;
  for(int i = 1;i<=n-1;i++) ans = max(ans,a[i]+b[i+1]);
  printf("%d\n",ans);
  return 0;
}