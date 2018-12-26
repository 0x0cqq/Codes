#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;

const int MAXN = 210000;

struct Node{
  int v,id;
  bool operator < (const Node &x)const{
    if(v != x.v)
      return v < x.v;
    else
      return id < x.id;
  }
};

vector<Node> v;

int n,m;
int a[MAXN];
ll k;

struct BIT{
  int sumn[MAXN+10];
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    while(x){
      ans += sumn[x];
      x -= lowbit(x);
    }
    return ans;
  }
  void update(int x,int v){
    while(x <= n){
      sumn[x] += v;
      x += lowbit(x);
    }
  }
}LT,RT;


void init(){
  scanf("%lld %lld",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
    v.push_back((Node){a[i],i});
  }
  sort(v.begin(),v.end());
  for(int i = 0;i<n;i++){
    a[v[i].id] = i+1;
  }
  // for(int i = 0;i<n;i++){
  //   printf("%lld\n",a[i+1]);
  // }
}

void solve(){
  int R = n,ans = 0;//(R,n]
  int ANS = 0;
  while(R >= 1){
    if(ans + RT.query(a[R]) > k) break;
    ans += RT.query(a[R]);
    RT.update(a[R],1);
    R--;
  }
  for(int i = 1;i<=n;i++){
    // printf("i:%lld R:%lld ans:%lld\n",i,R+1,ans);
    while(R < i){
      R++;
      RT.update(a[R],-1);
      ans -= RT.query(a[R]);
      ans -= LT.query(n) - LT.query(a[R]);      
    }
    ans += LT.query(n) - LT.query(a[i]);
    ans += RT.query(a[i]);
    // printf("ans:%lld\n",ans);
    LT.update(a[i],1);

    while(ans > k && R <= n-1){
      R++;
      RT.update(a[R],-1);
      ans -= RT.query(a[R]);
      ans -= LT.query(n) - LT.query(a[R]);
    }
    ANS += min(n-R,n-i);
    // printf("R:%lld ANS:%lld\n",R+1,ANS);
  }
  printf("%lld\n",ANS);
}


signed main(){
  init();
  solve();
  return 0;
}