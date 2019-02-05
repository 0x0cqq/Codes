#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct SAM{
  int c[MAXN][26],l[MAXN],fa[MAXN],rt,last,cnt,siz[MAXN];
  void init(){rt = last = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  void ins(int x){
    int p = last,np = newnode(l[p]+1);last = np;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = rt;
    else{
      int q = c[p][x];
      if(l[q] == l[p] + 1) fa[np] = q;
      else{
        int nq = newnode(l[p] + 1);
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[np] = fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np] = 1;
  } 
  void solve(int k){
    static int cn[MAXN],a[MAXN];
    static ll sum[MAXN];// 从这个点能走到多少个子串，无论相同 or 不同
    memset(sum,0,sizeof(sum));
    memset(cn,0,sizeof(cn));
    // sort
    for(int i = 1;i<=cnt;i++) cn[l[i]]++;
    for(int i = 1;i<=cnt;i++) cn[i] += cn[i-1];
    for(int i = cnt;i>=1;--i) a[cn[l[i]]--] = i;
    for(int i = cnt;i>=1;--i){
      int x = a[i];
      siz[fa[x]] += siz[x];
    }
    for(int i = cnt;i>=1;--i){
      int x = a[i];
      sum[x] = siz[x];
      for(int j = 0;j<26;j++)if(c[x][j]){
        sum[x] += sum[c[x][j]];
      }
    }
    // for(int i = 1;i<=cnt;i++){
    //   printf("%d:%lld(fa:%d len:%d siz:%d)\n",i,sum[i],fa[i],l[i],siz[i]);
    //   printf("  c:\n");
    //   for(int j = 0;j<26;j++){
    //     if(c[i][j] != 0)
    //       printf("    %c:%d\n",char(j+'a'),c[i][j]);
    //   }
    // }
    vector<char> ans;
    int x = rt;
    bool flag = 1;
    while(true){
      // printf("%d:%d\n",x,k);
      if(k <= siz[x]) break;
      k -= siz[x];
      bool f = 0;
      for(int i = 0;i<26;i++)if(c[x][i]){
        if(k <= sum[c[x][i]]){
          x = c[x][i];
          f = 1; ans.push_back(i + 'a');
          break;
        }
        else{
          k -= sum[c[x][i]];
        }
      }
      if(f == 0){ flag = 0;break; }
    }
    if(flag == 0){
      printf("No such line.\n");
    }
    else{
      for(auto ch : ans) putchar(ch);
      printf("\n");
    }
  }
}SAM;

int n,k;
char s[MAXN];
int main(){
  scanf("%s",s+1);n = strlen(s+1);
  SAM.init();
  for(int i = 1;i<=n;i++) SAM.ins(s[i]-'a');
  scanf("%d",&k);
  SAM.solve(k+n);
  return 0;
}