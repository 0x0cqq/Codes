#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1100000;
char s[MAXN];
int f[MAXN][3],g[MAXN][3];// 0 绿 1 蓝 2 红
int cnt,pos;

void solve(int nown){
  if(s[pos] == '0'){
    pos++;
    f[nown][0] = 1,f[nown][1] = f[nown][2] = 0;
    g[nown][0] = 1,g[nown][1] = g[nown][2] = 0;
    return;
  }
  else if(s[pos] == '1'){
    pos++;
    int ls = ++cnt;
    solve(ls);
    f[nown][0] = max(f[ls][1],f[ls][2]) + 1;
    f[nown][1] = max(f[ls][0],f[ls][2]);
    f[nown][2] = max(f[ls][0],f[ls][1]);
    g[nown][0] = min(g[ls][1],g[ls][2]) + 1;
    g[nown][1] = min(g[ls][0],g[ls][2]);
    g[nown][2] = min(g[ls][0],g[ls][1]);
    return;   
  }
  else{
    pos++;
    int ls = ++cnt,rs = ++cnt;
    solve(ls),solve(rs);
    f[nown][0] = max(f[nown][0],f[ls][1] + f[rs][2] + 1);
    f[nown][0] = max(f[nown][0],f[ls][2] + f[rs][1] + 1);
    f[nown][1] = max(f[nown][1],f[ls][0] + f[rs][2]);
    f[nown][1] = max(f[nown][1],f[ls][2] + f[rs][0]);
    f[nown][2] = max(f[nown][2],f[ls][1] + f[rs][0]);
    f[nown][2] = max(f[nown][2],f[ls][0] + f[rs][1]);
    g[nown][0] = g[nown][1] = g[nown][2] = 0x3f3f3f3f;
    g[nown][0] = min(g[nown][0],g[ls][1] + g[rs][2] + 1);
    g[nown][0] = min(g[nown][0],g[ls][2] + g[rs][1] + 1);
    g[nown][1] = min(g[nown][1],g[ls][0] + g[rs][2]);
    g[nown][1] = min(g[nown][1],g[ls][2] + g[rs][0]);
    g[nown][2] = min(g[nown][2],g[ls][1] + g[rs][0]);
    g[nown][2] = min(g[nown][2],g[ls][0] + g[rs][1]);  
  }
}

int main(){
  scanf("%s",s);
  solve(++cnt);
  int ans1 = max(f[1][0],max(f[1][1],f[1][2]));
  int ans2 = min(g[1][0],min(g[1][1],g[1][2]));
  printf("%d %d\n",ans1,ans2);
  return 0;
}