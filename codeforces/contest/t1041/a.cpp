#include <cstdio>
#include <algorithm>
using namespace std;


int n;
int num[200000];

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);  
  }
  sort(num+1,num+n+1);
  printf("%d\n",num[n]-num[1]+1-n);
  return 0;
}