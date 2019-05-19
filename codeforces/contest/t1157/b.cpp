#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];
int f[20];

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  for(int i = 1;i<=9;i++) scanf("%d",&f[i]);
  bool flag = 0;
  for(int i = 1;i<=n;i++){
    int t = s[i] - '0';
    if(f[t] > t) s[i] = f[t] + '0',flag = 1;
    else{
      if(f[t] == t && flag == 1) continue;
      else if(flag == 1) break;
    }
  }
  printf("%s",s+1);
}