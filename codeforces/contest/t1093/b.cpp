#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11000;

int n;
char s[MAXN];
int times[MAXN];

void judge(){
  scanf("%s",s);
  int l = strlen(s);
  memset(times,0,sizeof(times));
  for(int i = 0;i<l;i++){
    times[int(s[i])]++;
  }
  for(int i = 'a';i<='z';i++){
    if(times[i] == l){
      printf("-1\n");
      return;
    }
  }
  for(int i = 'a';i<='z';i++){
    for(int j = 0;j<times[i];j++)
      printf("%c",i);
  }
  putchar('\n');
}

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    judge();
  }
  return 0;
}