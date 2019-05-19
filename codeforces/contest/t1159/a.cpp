#include <bits/stdc++.h>
using namespace std;


const int MAXN = 110;

int n;
char s[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s);
  int now = 0,minn = 0;
  for(int i = 0;i<n;i++){
    now += s[i] == '+' ? 1 : -1;
    minn = min(minn,now);
  }
  printf("%d\n",-minn+now);
  return 0;
}