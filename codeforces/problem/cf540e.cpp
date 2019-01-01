#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 101000,logn = 35;

struct SegTree{
  int sumn[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn],cnt = 0;
  #define mid ((l+r)/2)
  void update(int &nown,int l,int r,int pos,int v){
    if(!nown) nown = ++cnt;
    if(l == r)
      sumn[nown] += v;
    else{
      sumn[nown] += v;
      if(pos <= mid) update(ls[nown],l,mid,pos,v);
      if(pos >= mid+1) update(rs[nown],mid+1,r,pos,v);
    }
  }
  int query(int nown,int l,int r,int ql,int qr){
    if(ql > qr) return qr - ql + 1;//以便后面对掉
    if(!nown) return 0;
    if(ql <= l && r <= qr)
      return sumn[nown];
    else{
      int ans = 0;
      if(ql <= mid) ans += query(ls[nown],l,mid,ql,qr);
      if(qr >= mid+1) ans += query(rs[nown],mid+1,r,ql,qr);
      return ans;
    }
  }
}T1,T2;

int n,MAX = 1e9;

map<int,int> S; // pos->val
int getval(int x){return S.count(x)?S[x]:x;}

void _swap(int a,int b){
  int va = getval(a),vb = getval(b);
  S[a] = vb,S[b] = va;
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    _swap(a,b);
  }
}

ll ans = 0;
int rt1,rt2;

void solve(){
  for(auto it = S.begin();it!=S.end();it++){
    T1.update(rt1,1,MAX,it->first,1);
  }
  for(auto it = S.begin();it!=S.end();it++){
    int p = it->first,v = it->second;
    ans += ((p-1)-(v+1)+1) - T1.query(rt1,1,MAX,v+1,p-1);//前面比他大的
    ans += ((v-1)-(p+1)+1) - T1.query(rt1,1,MAX,p+1,v-1);//后面比其他小的
  }
  for(auto it = S.begin();it!=S.end();it++){
    int v = it->second;
    ans += T2.query(rt2,1,MAX,v+1,MAX);
    T2.update(rt2,1,MAX,v,1);
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}