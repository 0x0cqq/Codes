#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110000,logn = 19;

int c[MAXN*logn*2][2],sum[MAXN*logn*2],totp;
struct Query{int id,l,r,x;};
struct Node{int tim,p,v;};
bool cmp(Node a,Node b){return a.p < b.p;}

vector<Query> Q[MAXN<<2];// query
vector<Node> N[MAXN<<2];// node / number

int query(int lc,int rc,int v){
  int ans = 0;
  for(int i = logn-1;i>=0;--i){
    ans <<= 1;int t = (v>>i) & 1;
    if(sum[c[rc][t^1]] - sum[c[lc][t^1]] > 0)
      lc = c[lc][t^1],rc = c[rc][t^1],ans ^= 1;
    else  lc = c[lc][t],rc = c[rc][t];
  }
  return ans;
}

void modify(int &x,int pre,int v){
  int now = x = ++totp;
  for(int i = logn-1;i>=0;--i){
    int t = (v>>i) & 1;
    c[now][t] = ++totp,c[now][t^1] = c[pre][t^1];
    sum[now] = sum[pre]+1;
    now = c[now][t],pre = c[pre][t];
  }
  sum[now] = sum[pre] + 1;
}

#define mid ((l+r)/2)
#define lson (x<<1)
#define rson (x<<1|1)
void addq(int x,int l,int r,int ql,int qr,Query q){
  if(qr < l || ql > r || ql > qr) return;
  if(ql <= l && r <= qr) Q[x].push_back(q);
  else{
    if(ql <= mid) addq(lson,l,mid,ql,qr,q);
    if(qr >= mid+1) addq(rson,mid+1,r,ql,qr,q);
  }
}

int rt[MAXN],tmp[MAXN],ans[MAXN];

void solve(int x,int l,int r){
  if(N[x].size() == 0) return;
  tmp[0] = totp = 0;// 清空 Trie
  tmp[++tmp[0]] = 0,rt[1] = 0;
  for(int i = 0;i < (int)(N[x].size());i++){
    tmp[++tmp[0]] = N[x][i].p;
    rt[tmp[0]] = 0,modify(rt[tmp[0]],rt[tmp[0]-1],N[x][i].v);
    if(l == r) continue;
    if(N[x][i].tim <= mid) N[lson].push_back(N[x][i]);
    else                   N[rson].push_back(N[x][i]);
  }
  for(int i = 0;i < (int)(Q[x].size());i++){
    int L = upper_bound(tmp+1,tmp+tmp[0]+1,Q[x][i].l-1) - tmp - 1;
    int R = upper_bound(tmp+1,tmp+tmp[0]+1,Q[x][i].r) - tmp - 1;
    ans[Q[x][i].id] = max(ans[Q[x][i].id],query(rt[L],rt[R],Q[x][i].x));
  }
  if(l == r) return;
  solve(lson,l,mid),solve(rson,mid+1,r);
}

int n,m,tott,totq;
int val[MAXN];

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&val[i]);
  totp = 0;
  for(int i = 1;i<=n;i++) rt[i] = 0,modify(rt[i],rt[i-1],val[i]);
  int op,L,R,x,d,s,v;
  for(int i = 1;i<=m;i++){
    scanf("%d",&op);
    if(op == 0){
      scanf("%d %d",&s,&v);
      tott++;
      N[1].push_back((Node){tott,s,v});
    }
    else if(op == 1){
      scanf("%d %d %d %d",&L,&R,&x,&d);
      ++totq;
      addq(1,1,m,tott-d+1,tott,(Query){totq,L,R,x});
      ans[totq] = query(rt[L-1],rt[R],x);
    }
  }
  sort(N[1].begin(),N[1].end(),cmp);
  solve(1,1,m);
  for(int i = 1;i<=totq;i++) printf("%d\n",ans[i]);
  return 0;
}