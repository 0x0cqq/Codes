#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d\n",&a[i]);
    printf("%d\n",max(1,(a[i]-1)/7 + 1));
  }
  return 0;
}