#include <cstdio>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 110000;

int n,m,k,Q;
int num[MAXN];
int xor1[MAXN];
int xor2[MAXN];
int ans[MAXN];

struct Query{
  int l,r,id;
  bool operator <(const Query _q)const{
    if(l/Q != _q.l/Q){
      return l/Q < _q.l/Q;
    }
    else{
      return r < _q.r;
    }
  }
}q[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&k);
  Q = sqrt(n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&q[i].l,&q[i].r);
    q[i].id = i;
  }
  sort(q+1,q+m+1);
}

void build(){
  for(int i = 1;i<=n;i++){
    xor1[i] = xor1[i-1] ^ num[i];
    xor2[i] = xor2[i-1] ^ num[i];
  }
  for(int i = 0;i<=n;i++){
    xor2[i] ^= k;
  }
  for(int i = n;i>=0;i--){
    xor2[i+1] = xor2[i];
  }
	// for(int i = 1;i<=n;i++){
	// 	printf("%d: xor1:%d xor2:%d\n",i,xor1[i],xor2[i]);
	// }
}

ll ANS = 0;
ll num1[MAXN],num2[MAXN];

void addl(int pos){
  num1[xor1[pos]]++;
  num2[xor2[pos]]++;
  ANS += num1[xor2[pos]];
}

void addr(int pos){
  num1[xor1[pos]]++; 
  num2[xor2[pos]]++; 
  ANS += num2[xor1[pos]];
}

void dell(int pos){
  ANS -= num1[xor2[pos]];
  num1[xor1[pos]]--;
  num2[xor2[pos]]--;
}

void delr(int pos){
  ANS -= num2[xor1[pos]];
  num1[xor1[pos]]--;
  num2[xor2[pos]]--;  
}

void solve(){
  int L = 1,R = 0;
  for(int i = 1;i<=m;i++){
    while(q[i].l < L) addl(--L);
    while(R < q[i].r) addr(++R);
    while(L < q[i].l) dell(L++);
    while(q[i].r < R) delr(R--); 
    // printf("----------------------\n");
    // printf("%d: ANS:%lld q:%d %d L,R:%d %d\n",q[i].id,ANS,q[i].l,q[i].r,L,R);
    // for(int i = 1;i<=12;i++){
    //   printf("%d:%lld %lld\n",i,num1[i],num2[i]);
    // }
    ans[q[i].id] = ANS;
  }
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  } 
}

int main(){
  init();
  build();
  solve();
  return 0;
}