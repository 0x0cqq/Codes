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
  if(t[a].p != t[b].p)
    return t[a].p < t[b].p;
  else
    return t[a].l < t[b].l;
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
  int p,l;
  bool operator < (const T &w)const{
    if(p != w.p)
      return p < w.p;
    else
      return l < w.l;
  }
};


multiset<T> K;
int pos = 0;//[1,pos]

bool cmp2(const int a,const int b){
  return q[a].g < q[b].g;
}

int a[MAXN];


void solve(int ql,int qr,int l,int r){// *a 存储询问编号 在 [l,r] 果汁内二分
  // printf("ql,qr:%lld %lld L:%lld R:%lld mid:%lld pos:%lld\n",ql,qr,l,r,(l+r)>>1,pos);
  if(ql > qr) return;
  // printf("  a:");
  // for(int i = ql;i<=qr;i++){
  //   printf("%lld ",a[i]);
  // }
  // printf("\n");
  if(l == r){
    for(int i = ql;i<=qr;i++){
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
    pos++;
    //printf("i:%lld\n",pos);
    K.insert((T){t[pos].p,t[pos].l});
  }
  while(pos > mid){
    K.erase(K.lower_bound((T){t[pos].p,t[pos].l}));
    //printf("e:%lld\n",pos);
    pos--;
  }
  ll G = 0,L = 0,acnt = 0,bcnt = 0;
  sort(a+ql,a+qr+1,cmp2);
  multiset<T>::iterator it = K.begin();
  #define xp it->p
  #define xl it->l
  ll cnt = 0;
  for(int i = ql;i<=qr;i++){
    while(it != K.end() && G + xp * xl <= q[a[i]].g){
      G += xp * xl;
      L += xl;
      it++;
      cnt++;
    }
    //printf("  %lld a[i]:%lld G:%lld L:%lld cnt:%lld | q: g:%lld l:%lld KK:%d ",i,a[i],G,L,cnt,q[a[i]].g,q[a[i]].l,(signed)(it!=K.end()));
    if(L >= q[a[i]].l ||
      (it != K.end() && (q[a[i]].l-L) * xp + G <= q[a[i]].g))
      a1[acnt++] = a[i];//,printf(" GO:1\n");
    else
      a2[bcnt++] = a[i];//,printf(" GO:2\n");
  }
  // printf("  a1:");
  // for(int i = 0;i<acnt;i++){
  //   printf("%lld ",a1[i]);
  // }
  // printf("\n");
  // printf("  a2:");
  // for(int i = 0;i<bcnt;i++){
  //   printf("%lld ",a2[i]);
  // }
  // printf("\n");  
  memcpy(a + ql,a1,sizeof(int)*acnt),memcpy(a + qr-bcnt+1,a2,sizeof(int)*bcnt);
  // printf("-------------------------\n");  
  solve(ql,ql+acnt-1,l,mid),solve(qr-bcnt+1,qr,mid+1,r);
  #undef p
  #undef l
}

void solve(){
  for(int i = 1;i<=m;i++)
    a[i] = i;
  t[n+1].d=-1;t[n+1].p=0;t[n+1].l=1e18;++n;
  solve(1,m,1,n);
  for(int i = 1;i<=m;i++)
    printf("%lld\n",ans[i]);
}

signed main(){
  init();
  solve();
  return 0;
}