#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 1100000,MAXQ = 50000;

void read(int &x){scanf("%d",&x);}
void read(char *x){scanf("%s",x);}

int n,m,a[MAXN],Q;

void init(){
  read(n),read(m);Q = sqrt(n)+1;
  for(int i = 0;i<n;i++){
    read(a[i]);
  }
}

void modify(int l,int r,int w){
  for(int i = l;i<=r;i++)
    a[i] += w;
}

int query(int l,int r,int c){
  int ans = 0;
  for(int i = l;i<=r;i++){
    if(a[i] >= c){
      ans++;
    }
  }
  return ans;
}


void solve(){
  char op[10];
  int l,r,c;
  for(int i = 1;i<=m;i++){
    read(op),read(l),read(r),read(c);
    if(op[0] == 'M'){
      modify(l-1,r-1,c);
    }
    if(op[0] == 'A'){
      printf("%d\n",query(l-1,r-1,c));
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}