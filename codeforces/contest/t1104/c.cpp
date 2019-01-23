#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];

int nowa = 1,nowb = 1;

int main(){
  scanf("%s",s);
  n = strlen(s);
  for(int i = 0;i<n;i++){
    if(s[i] == '0'){
      printf("%d %d\n",1,(nowa-1)%4+1);
      nowa += 1;
    }
    else{
      printf("%d %d\n",4,nowb%4);
      nowb += 2;
    }
  }
  return 0;
}