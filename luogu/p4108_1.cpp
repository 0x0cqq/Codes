#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;

const int MAXN = 210000,MAXQ = 5000;

inline int gcd(int a,int b){
  return b==0?a:gcd(b,a%b);
}

struct Node{
  ll num;int  pos;
  Node(ll _num = 0,int _pos = 0){
    num = _num,pos = _pos;
  }
  bool operator < (const Node &_n)const{
    if(num != _n.num){
      return num < _n.num;
    }
    else{
      return pos < _n.pos;
    }
  }
};



int n,q,Q;
int num[MAXN];
int block[MAXN],lb[MAXQ],rb[MAXQ];
int GCD[MAXQ],XOR[MAXQ];

Node S[MAXN];

void init(){
  scanf("%d",&n);
  Q = sqrt(n) + 1;
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 1;i<=n;i++){
    block[i] = i/Q+1;
    if(block[i] != block[i-1]){
      lb[block[i]] = i;
      rb[block[i-1]] = i-1;
    }
  }
  rb[block[n]] = n;
  for(int i = 1;i<=n;i++){
    GCD[block[i]] = gcd(num[i],GCD[block[i]]);
    XOR[block[i]] = num[i] ^ XOR[block[i]];
  }
  for(int i = 1;i<=block[n];i++){
    int ans = 0;
    for(int p = lb[i];p<=rb[i];p++){
      ans ^= num[p];
      S[p] = (Node(ans,p));
    }
    sort(S+lb[i],S+rb[i]+1);
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d: num:%d block:%d\n",i,num[i],block[i]);
  // }
  // for(int i = 1;i<=block[n];i++){
  //   printf("%d: lb,rb:%d %d GCD:%d XOR:%d\n",i,lb[i],rb[i],GCD[i],XOR[i]);
  // }
}

inline void modify(int pos,int v){
  //printf("modify:%d %d\n",pos,v);
  num[pos] = v;
  int b = block[pos];GCD[b] = XOR[b] = 0;
  for(int i = lb[b];i<=rb[b];i++){
    GCD[b] = gcd(GCD[b],num[i]);
    XOR[b] ^= num[i];
    S[i] = Node(XOR[b],i);
  }
  sort(S+lb[b],S+rb[b]+1);
}

inline int erfen(int b,int nowg,int nowx,ll val){
  // printf("erfen: b:%d nowg:%d nowx:%d val:%lld\n",b,nowg,nowx,val);
  if(val % nowg) return -1;
  val/=nowg;
  val ^= (ll)(nowx);
  // printf("erfen: b:%d nowg:%d nowx:%d val:%lld\n",b,nowg,nowx,val);
  Node *it = lower_bound(S+lb[b],S+rb[b]+1,Node(val,0));
  // for(set<Node>::iterator its = S[b].begin();its!=S[b].end();its++){
  //   printf("num:%lld pos:%d equal:%d\n",its->num,its->pos,int(its==it));
  // }
  if(it <= S + rb[b] && it->num == val)
    return it->pos;
  else
    return -1;
}

inline int baoli(int b,int nowg,int nowx,ll val){
  // printf("baoli: b:%d nowg:%d nowx:%d val:%lld\n",b,nowg,nowx,val);
  for(int i = lb[b];i<=rb[b];i++){
    nowg = gcd(nowg,num[i]);
    nowx = nowx ^ num[i];
    if(1LL * nowg * nowx == val){
      return i;
    }
  }
  return -1;
}

int query(ll val){
  int nowgcd = 0,nowxor = 0; 
  for(int i = 1;i<=block[n];i++){
    int nex = gcd(nowgcd,GCD[i]),now = gcd(nowgcd,num[lb[i]]);
    int t = -1;
    if(now == nex){
      t = erfen(i,now,nowxor,val);
    }
    else{
      t = baoli(i,nowgcd,nowxor,val);
    }
    nowgcd = nex,nowxor ^= XOR[i];
    if(t != -1) return t;
  }
  return -1;
}

void solve(){
  scanf("%d",&q);
  char op[MAXN];int id = 0,x = 0;ll v = 0;
  for(int i = 1;i<=q;i++){
    scanf("%s",op);
    if(op[0] == 'M'){
      scanf("%d %d",&id,&x);
      id++;
      modify(id,x);
    }
    else if(op[0] == 'Q'){
      scanf("%lld",&v);
      int t = query(v);
      if(t != -1){
        printf("%d\n",t-1);
      }
      else{
        printf("no\n");
      }
    }
  }
}



int main(){
  init();
  solve();
  return 0;
}