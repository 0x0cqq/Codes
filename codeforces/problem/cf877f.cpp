#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 110000;

int n,q,Q;
int t[MAXN],a[MAXN];
ll k,sum[MAXN],A[MAXN],B[MAXN];// A -> -k / B -> +k
map<ll,int> S;int tmpcnt = 0;

struct Query{
  int l,r,id;
}qu[MAXN];

bool cmp(Query a,Query b){
  if(a.l/Q != b.l/Q)
    return a.l / Q < b.l / Q;
  else
    return ((a.l/Q)&1)?a.r < b.r:a.r > b.r;
}

void init(){
  scanf("%d %lld",&n,&k);
  for(int i = 1;i<=n;i++) scanf("%d",&t[i]);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 1;i<=n;i++){
    sum[i] = t[i] == 1?a[i]:-a[i];
    sum[i] += sum[i-1];
    S[sum[i]] = 0;
  }
  S[0] = 0;
  for(auto it = S.begin();it != S.end();it++)
    it->second = ++tmpcnt;
  for(int i = 0;i<=n;i++){
    if(S.count(sum[i]-k)) A[i] = S[sum[i]-k];
    if(S.count(sum[i]+k)) B[i] = S[sum[i]+k];
    sum[i] = S[sum[i]];
  }
  Q = sqrt(n);
  scanf("%d",&q);
  for(int i = 1;i<=q;i++)
    scanf("%d %d",&qu[i].l,&qu[i].r),qu[i].id = i;
  sort(qu+1,qu+q+1,cmp);
}

static int cnt[MAXN],L = 1,R = 0;// 维护 [L-1,R] 的前缀和
ll ans = 0;
void addL(int pos){// 加上pos-1的前缀和
  ans += cnt[B[pos-1]];
  cnt[sum[pos-1]]++;
}
void addR(int pos){
  ans += cnt[A[pos]];
  cnt[sum[pos]]++;
}
void delL(int pos){
  cnt[sum[pos-1]]--;
  ans -= cnt[B[pos-1]];
}
void delR(int pos){
  cnt[sum[pos]]--;
  ans -= cnt[A[pos]];
}

ll ANS[MAXN];

void solve(){
  cnt[S[0]] = 1;
  for(int i = 1;i<=q;i++){
    while(qu[i].l < L) addL(--L);
    while(qu[i].r > R) addR(++R);
    while(qu[i].l > L) delL(L++);
    while(qu[i].r < R) delR(R--);
    ANS[qu[i].id] = ans;
    // printf("%d %d ANS:%lld\n",qu[i].l,qu[i].r,ans);
  }
  for(int i = 1;i<=q;i++){
    printf("%lld\n",ANS[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}