#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000,LOGN = 31;

namespace Tree{
  int sumn[MAXN*LOGN],ls[MAXN*LOGN],rs[MAXN*LOGN],cnt = 1;
  void upd(int nown,int v){
    static int tmp[40];int ecnt = 0;
    for(int i = nown;i;i>>=1) tmp[++ecnt] = i&1;
    int now = 1;
    for(int i = ecnt-1;i>=0;--i){
      sumn[now] += v;
      if(tmp[i] == 0){
        if(!ls[now]) ls[now] = ++cnt;
        now = ls[now];
      }
      else{
        if(!rs[now]) rs[now] = ++cnt;
        now = rs[now];
      }
    }
  }
  double decay(){
    int now = 1,nowmax = -1e9;
    double ans = 0, p = 1;
    while(now != 0){// now 非空
      int lson = sumn[ls[now]],rson = sumn[rs[now]],val = sumn[now] - lson - rson;
      p *= 0.5;
      ans += p * max(nowmax,max(lson,rson)+val);
      if(lson > rson){
        nowmax = max(nowmax,rson+val);
        now = ls[now];
      }
      else{
        nowmax = max(nowmax,lson+val);
        now = rs[now];
      }
    }
    ans += p * nowmax;
    return ans;
  }
}

int h,q;

void init(){
  scanf("%d %d",&h,&q);
}

void solve(){
  for(int i = 1;i<=q;i++){
    char s[12];
    int a,b;
    scanf("%s",s);
    if(s[0] == 'a'){
      scanf("%d %d",&a,&b);
      Tree::upd(a,b);
    }
    else if(s[0] == 'd'){
      printf("%.8lf\n",Tree::decay());
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}