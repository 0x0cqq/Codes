#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n;
int s[MAXN];
int last[MAXN];
map<int,int> l;

namespace Hash{
  const ll base = 131,mod = 1e9+7;
  ll p[MAXN],h[MAXN];
  void init(){// from n, s[]
    p[0] = 1; 
    for(int i = 1;i<=n;i++) p[i] = (p[i-1]*base)%mod;
    for(int i = 1;i<=n;i++) h[i] = (h[i-1] * base + s[i]) % mod;
  }
  ll gethash(int l,int r){
    ll tmp = (h[r] - h[l-1] * p[r-l+1])%mod;
    return tmp < 0 ? tmp+mod : tmp;
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&s[i]);
    if(!l.count(s[i])) last[i] = 0;
    else last[i] = l[s[i]];
    l[s[i]] = i;
  }
  Hash::init();
}

struct Node{
  int pos,len;//记录第二个的开始位置和长度
  bool operator < (const Node &x)const{
    if(len != x.len)
      return len < x.len;
    else
      return pos < x.pos;
  }
};

vector<Node> v;

bool judge(int a,int b){
  if(a > b) swap(a,b);
  if(a == b) return 0;
  int l = b-a;
  return Hash::gethash(a,a+l-1) == Hash::gethash(b,b+l-1);
}

vector<int> tmp;//pos


void add(int x){
  tmp.clear();
  while(x != 0){
    tmp.push_back(x);
    x = last[x];
  }
  sort(tmp.begin(),tmp.end());
  for(unsigned i = 0;i<tmp.size();i++){
    for(unsigned j = i+1;j<tmp.size();j++){
      // printf("%d %d judge:%d\n",tmp[i],tmp[j],int(judge(tmp[i],tmp[j])));
      if(judge(tmp[i],tmp[j])){
        v.push_back((Node){tmp[j],tmp[j]-tmp[i]});
      }
    }
  }
}

void solve(){
  static int vis[MAXN];
  for(int i = 1;i<=n;i++){
    if(vis[i] == 1) continue;
    add(i);
  }
  sort(v.begin(),v.end());
  int pos = 1;// 最左边开始的位置
  for(unsigned i = 0;i<v.size();i++){
    Node t = v[i];
    // printf("t:%d %d now:%d\n",t.pos,t.len,pos);
    if(t.pos - t.len >= pos) pos = t.pos;
  }
  printf("%d\n",n-pos+1);
  for(int i = pos;i<=n;i++){
    printf("%d ",s[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}