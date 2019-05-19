#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int n,m;
int a[MAXN][MAXN];
typedef bitset<MAXN> bs;

bs row[MAXN],A,B,T;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=m;j++)
      scanf("%d",&a[i][j]),row[i][j] = a[i][j];
  for(int i = 1;i<=m;i++) T[i] = 1;
}

bs judge(int x,int y,bs col_rev){
  bs tmp = 0,ans = 0;// 第 0 位用来存可行与否
  for(int i = 1;i<=x-1;i++){// 全都是 0
    tmp = row[i] ^ col_rev;
    if(int(tmp.count()) == 0) ans[i] = 0;
    else if(int(tmp.count()) == m) ans[i] = 1;
    else {ans[0] = 1;return ans;}
  }
  // 1 ～ y-1 是 0，y ～ m 是 1
  tmp = row[x] ^ col_rev;
  bs need = 0;
  // printf("tmp:\n");
  // for(int i = 0;i<=MAXN-1;i++) printf("%d",int(tmp[i]));
  // printf("\n");
  for(int j = 1;j<=m;j++) need[j] = (j >= y);
  // printf("need:\n");
  // for(int i = 0;i<=MAXN-1;i++) printf("%d",int(need[i]));
  // printf("\n");
  if(tmp == need) ans[x] = 0;
  else if(((~tmp) & T) == need) ans[x] = 1;
  else {ans[0] = 1;return ans;} 
  //----
  for(int i = x+1;i<=n;i++){
    tmp = row[i] ^ col_rev;
    if(int(tmp.count()) == 0) ans[i] = 1;
    else if(int(tmp.count()) == m) ans[i] = 0;
    else {ans[0] = 1;return ans;}
  }
  return ans;
}

bool judge(int x,int y){
  bs col_rev = 0,tmp = 0;
  if(x == 1){
    for(int j = 1;j <= y-1;j++) col_rev[j] = row[1][j];
    for(int j = y;j <= m;j++)   col_rev[j] = row[1][j]^1;
  }
  else col_rev = row[1];
  // printf("%d %d:\n",x,y);
  // for(int i = 1;i<=m;i++) printf("%d",int(col_rev[i]));
  // printf("\n");
  tmp = judge(x,y,col_rev);
  // for(int i = 0;i<=n;i++) printf("t%d",int(tmp[i]));
  // printf("\n");  
  if(tmp[0] == 0){
    A = tmp,B = col_rev;
    return 1;
  }
  tmp = judge(x,y,(~col_rev)&T);
  if(tmp[0] == 0){
    A = tmp,B = (~col_rev) & T;
    return 1;
  }
  return 0;
}

void solve(){
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){ // 第一个出现 1 的位置
      if(judge(i,j)){
        printf("YES\n");
        for(int i = 1;i<=n;i++) putchar('0' + A[i]);
        putchar('\n');
        for(int i = 1;i<=m;i++) putchar('0' + B[i]);
        putchar('\n');
        return;
      }
    }
  }
  printf("NO\n");
}

int main(){
  init();
  solve();
  return 0;
}