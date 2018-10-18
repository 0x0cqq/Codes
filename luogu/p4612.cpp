// Code By Chen Qiqian on 2018.10.16
#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m;

struct Node{
  ll d,p,l;
  bool operator < (const Node &a)const{
    if(d != a.d)
      return d > a.d;
    else
      return p < a.p;
  }
}t[MAXN];


bool cmp(const int &a,const int &b){
  return t[a].p < t[b].p;
}

struct Query{
  ll g,l,id;
}q[MAXN];


int ans[MAXN];

void init(){
  scanf("%lld %lld",&n,&m);
  for(int i = 1;i<=n;i++){
    ll a,b,c;
    scanf("%lld %lld %lld",&a,&b,&c);
    t[i] = (Node){a,b,c};
  }
  sort(t+1,t+n+1);
  for(int i = 1;i<=m;i++){
    scanf("%lld %lld",&q[i].g,&q[i].l);
    q[i].id = i;
  }
}

ll a1[MAXN],a2[MAXN];

struct T{
  int v;
  bool operator < (const T &w)const{return cmp(v,w.v);}
};


set<T> K;
int pos = 0;//[1,pos]

bool cmp2(const int a,const int b){
  return q[a].g < q[b].g;
}


void solve(int *a,int n1,int l,int r){// *a 存储询问编号 在 [l,r] 果汁内二分
  if(!n1) return;
  //printf("n1:%lld L:%lld R:%lld mid:%lld\n",n1,l,r,(l+r)>>1);
  if(l == r){
    for(int i = 0;i<n1;i++){
      //printf("a:%lld id:%lld ans:%lld(%lld)\n",a[i],q[a[i]].id,t[l].d,l);
      ans[q[a[i]].id] = t[l].d;
    }
    return;
  }
  // 寻找到最小的需要的 n
  // d 按从大到小排序
  int mid = (l+r)>>1;
  //判断 1 -> mid 区间是否可以满足限制 (g_i,l_i)
  //维护multiset使其可以包括 [1,mid] 所有果汁
  while(pos < mid){
    pos++;K.insert((T){pos});
  }
  while(pos > mid){
    K.erase(K.lower_bound((T){pos}));pos--;
  }
  ll G = 0,L = 0,acnt = 0,bcnt = 0;
  sort(a,a+n1,cmp2);
  set<T>::iterator it = K.begin();
  #define x it->v
  ll cnt = 0;
  for(int i = 0;i<n1;i++){
    while(it != K.end() && G + t[x].p * t[x].l <= q[a[i]].g){
      G += t[x].p * t[x].l;
      L += t[x].l;
      it++;
      cnt++;
    }
    //printf("  %lld G:%lld L:%lld cnt:%lld | q: g:%lld l:%lld ",i,G,L,cnt,q[a[i]].g,q[a[i]].l);
    if(L >= q[a[i]].l ||
      (it != K.end() && q[a[i]].l-L <= t[x].l && (q[a[i]].l-L)*t[x].p + G <= q[a[i]].g))
      a1[acnt++] = a[i];//,printf(" GO:1\n");
    else
      a2[bcnt++] = a[i];//,printf(" GO:2\n");
  }
  memcpy(a,a1,sizeof(int)*acnt),memcpy(a+acnt,a2,sizeof(int)*bcnt);
  solve(a,acnt,l,mid),solve(a+acnt,bcnt,mid+1,r);
  #undef x
}

void solve(){
  static int qq[MAXN];
  for(int i = 1;i<=m;i++){
    qq[i] = i;
  }
  t[n+1].d=-1;t[n+1].p=0;t[n+1].l=1e18;++n;
  solve(qq+1,m,1,n+1);
  for(int i = 1;i<=m;i++)
    printf("%lld\n",ans[i]);
}

signed main(){
  init();
  solve();
  return 0;
}