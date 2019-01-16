#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;
const double pi = acos(-1);


int n,r;

int main(){
  scanf("%d %d",&n,&r);
  printf("%.10lf\n",double(r)/(1/sin(pi/n)-1));
  return 0;
}