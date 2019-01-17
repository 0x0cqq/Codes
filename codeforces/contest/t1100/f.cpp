#include <bits/stdc++.h>
using namespace std;

const int LOGN = 21,MAXN = 501000;

struct LB{
  int basis[LOGN],pos[LOGN];
  void insert(int x,int id){
    for(int i = LOGN-1;i>=0;--i){
      if(x & (1<<i)){
        if(!basis[i]){
          basis[i] = x;
          pos[i] = id;
          return;
        }
        else{
          if(pos[i] < id) swap(basis[i],x),swap(pos[i],id);
          x ^= basis[i];
        }
      }
    }
  }
  int query(int id){
    int ans = 0;
    for(int i = LOGN-1;i>=0;--i){
      if(pos[i] >= id && (ans^basis[i]) > ans)
        ans ^= basis[i];
    }
    return ans;
  }
}T;

int n,q;
int a[MAXN],ans[MAXN];

struct Node{
  int x,id;
};

vector<Node> Q[MAXN]; 

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    int l,r;
    scanf("%d %d",&l,&r);
    Q[r].push_back((Node){l,i});
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    T.insert(a[i],i);
    for(auto node : Q[i]){
      ans[node.id] = T.query(node.x);
    }
  }
  for(int i = 1;i<=q;i++){
    printf("%d\n",ans[i]);
  }
}


int main(){
  init();
  solve();
  return 0;
}