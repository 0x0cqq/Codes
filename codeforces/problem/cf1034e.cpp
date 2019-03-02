#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2100000;
int n,N,cnt[MAXN];
char s[MAXN],t[MAXN];
ll a[MAXN],b[MAXN],p[MAXN];

void fwt_or(ll *P,int n,int op){
  for(int i = 1;i<n;i<<=1){
    for(int j = 0;j<n;j += (i<<1)){
      for(int k = 0;k<i;k++){
        if(op == 1) P[j+i+k] += P[j+k];
        else P[j+i+k] -= P[j+k];
      }
    }
  }
}

int main(){
  scanf("%d",&n);N = (1<<n);
  scanf("%s %s",s,t);
  for(int i = 0;i<N;i++) a[i] = s[i] - '0',b[i] = t[i] - '0';
  for(int i = 0;i<N;i++) cnt[i] = cnt[i>>1] + (i & 1),p[i] = (1LL<<(2*cnt[i]));
  for(int i = 0;i<N;i++) a[i] = a[i] * p[i],b[i] = b[i] * p[i];
  fwt_or(a,N,1),fwt_or(b,N,1);
  for(int i = 0;i<N;i++) a[i] = a[i] * b[i];
  fwt_or(a,N,-1);
  for(int i = 0;i<N;i++) a[i] /= p[i];
  for(int i = 0;i<N;i++) putchar((a[i]&3)+'0');
  putchar('\n');
  return 0;
}