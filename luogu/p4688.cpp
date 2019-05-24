#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100050;
typedef bitset<MAXN> bs;

struct Node{
  int id,l,r;
};

int n,m,Q;
int a[MAXN],t[MAXN],sum[MAXN];
bs ans[MAXN/4];
bool cmp(Node a,Node b){
  return a.l / Q == b.l / Q ? a.r < b.r : a.l/Q < b.l/Q;
}
vector<Node> v;int CNT = 0; 
bs now = 0;
int cnt[MAXN];

void add(int x){
  cnt[a[x]]++,now[a[x]+cnt[a[x]]-1] = 1;
}
void del(int x){
  now[a[x]+cnt[a[x]]-1] = 0,cnt[a[x]]--;
}

void calc(){
  sort(v.begin(),v.end(),cmp);
  int L = 1,R = 0;
  now.reset();
  memset(cnt,0,sizeof(cnt));
  for(int i = 1;i<=CNT;i++) ans[i].set();
  for(auto q : v){
    while(L > q.l) add(--L);
    while(R < q.r) add(++R);
    while(L < q.l) del(L++);
    while(R > q.r) del(R--);
    // printf("%d L,R:%d %d\n",q.id,q.l,q.r);
    // for(int i = 1;i<=n;i++) printf("%d",int(now[i]));
    // printf("\n");
    ans[q.id] &= now;
  }
  for(int i = 1;i<=CNT;i++){
    printf("%d\n",sum[i]-3*int(ans[i].count()));
  }
}

void init(){
  scanf("%d %d",&n,&m),Q = sqrt(n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]),t[i] = a[i];
  sort(t+1,t+n+1);
  for(int i = 1;i<=n;i++) a[i] = lower_bound(t+1,t+n+1,a[i]) - t;
  // printf("a:\n");
  // for(int i = 1;i<=n;i++) printf("%d ",a[i]);
  // printf("\n");
}


void solve(){
  for(int i = 1;i<=m;i++){
    int l1,r1,l2,r2,l3,r3;++CNT;
    scanf("%d %d %d %d %d %d",&l1,&r1,&l2,&r2,&l3,&r3);
    v.push_back((Node){CNT,l1,r1});sum[CNT] += r1-l1+1;
    v.push_back((Node){CNT,l2,r2});sum[CNT] += r2-l2+1;
    v.push_back((Node){CNT,l3,r3});sum[CNT] += r3-l3+1;
    if(CNT == 25000){
      calc();
      v.clear();
      for(int i = 1;i<=CNT;i++) sum[i] = 0;
      CNT = 0;
    }
  }
  if(CNT) calc();
}


int main(){
  init();
  solve();
  return 0;
}