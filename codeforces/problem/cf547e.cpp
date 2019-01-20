#include <bits/stdc++.h>
#define ffff printf("f***!\n")
using namespace std;

const int inf = 1e9;

const int MAXN = 510000,LOGN = 20;

namespace SA{
  int s[MAXN],sa[MAXN],rk[MAXN],x[MAXN],y[MAXN],cnt[MAXN],ht[MAXN];
  void get_sa(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]]++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    for(int i = 1;i<n;i++) rk[sa[i]] = (s[sa[i]] == s[sa[i-1]]) ? m:++m;
    for(int j = 1;;j<<=1){
      if(++m == n) break;
      for(int i = 0;i<j;i++) y[i] = n-j+i;
      for(int i = 0,k = j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i]-j;
      for(int i = 0;i<n;i++) x[i] = rk[y[i]];
      for(int i = 0;i<m;i++) cnt[i] = 0;
      for(int i = 0;i<n;i++) cnt[x[i]]++;
      for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
      for(int i = n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
      m = rk[sa[0]] = 0;
      for(int i = 1;i<n;i++)
        rk[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+j] == y[sa[i-1]+j]) ? m : ++m;
    }
  }
  void getheight(int n){
    for(int i = 0,h = ht[0] = 0;i<n;i++){
      int j = sa[rk[i]-1];
      while(i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
      ht[rk[i]] = h;
      if(h) --h;
    }
  }
  void solve(int n,int *t,int m){
    for(int i = 0;i<n;i++) s[i] = t[i];
    s[n++] = 0;
    get_sa(n,m);
    // ffff;
    getheight(n);

    // printf(":\n");
    // for(int i = 0;i < n;i++) printf("%2d ",i);
    // printf("\n");
    // printf("s:\n");
    // for(int i = 0;i < n;i++) printf("%2d ",s[i]);
    // printf("\n");
    // printf("sa:\n");
    // for(int i = 0;i < n;i++) printf("%2d ",sa[i]);
    // printf("\n");
    // printf("rk:\n");
    // for(int i = 0;i < n;i++) printf("%2d ",rk[i]);
    // printf("\n");   
    // printf("ht:\n");
    // for(int i = 0;i < n;i++) printf("%2d ",ht[i]);
    // printf("\n");   
  }
}

namespace ST{
  int minn[MAXN][LOGN],_log[MAXN];
  void init(int n,int *t){
    _log[0] = -1;
    for(int i = 1;i<=n;i++)
      minn[i][0] = t[i],_log[i] = _log[i>>1] + 1;
    for(int j = 1;j<LOGN;j++)
      for(int i = 1;i+(1<<(j-1)) <= n;i++)
        minn[i][j] = min(minn[i][j-1],minn[i+(1<<(j-1))][j-1]);
  }
  int query(int l,int r){
    if(l == r+1) return inf;
    int len = log2(r-l+1);//_log[r-l+1];
    return min(minn[l][len],minn[r-(1<<len)+1][len]);
  }
}

namespace BIT{
  int n,sumn[MAXN];
  void init(int _n){n = _n;}
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    for(int i = x;i;i-=lowbit(i)) ans += sumn[i];
    return ans;
  }
  void update(int x,int v){
    if(!x) return;
    for(int i = x;i<=n;i+=lowbit(i)) sumn[i] += v;
  }
  int query(int l,int r){
    return query(r) - query(l-1);
  }
}

// int lcp(int x,int y){return ST::query(x,y);}

int tmp[MAXN],cnt = 0;
char s[MAXN];

int n,q;
int str_len[MAXN],st[MAXN],belong[MAXN]; // 每个字符串的长度，每个串的开始位置，每个位置属于的串

void init(){
  scanf("%d %d",&n,&q);
  for(int i = 1;i<=n;i++){
    scanf("%s",s);
    st[i] = cnt;
    int l = strlen(s);
    str_len[i] = l;
    for(int j = 0;j<l;j++) {
      belong[cnt] = i;
      tmp[cnt++] = s[j] - 'a' + 1;
    }
    tmp[cnt++] = 'z' - 'a' + i + 1;
  }
  // ffff;
  SA::solve(cnt,tmp,'z' - 'a' + n + 2);
  ST::init(cnt,SA::ht);
  // printf("be:\n");
  // for(int i = 0;i < cnt+1;i++){
  //   printf("%2d ",belong[SA::sa[i]]);
  // }
  // printf("\n");
}

pair<int,int> getrange(int pos,int len){// 返回字符串的 pos 位置在 sa 数组中两侧能到的位置
  // printf("q:%d %d\n",pos,len);
  pair<int,int> ans(0,0);
  int p = SA::rk[pos],L = 0,R = p;
  while(L!=R){
    int mid = (L+R)/2,t = ST::query(mid+1,p);
    // printf("mid+1:%d p:%d ans:%d\n",mid+1,p,t);
    if(t >= len) // mid 与 pos 的 len 
      R = mid;
    else
      L = mid+1;
  }
  ans.first = L;
  L = p,R = cnt;
  while(L!=R){
    int mid = (L+R+1)/2;
    if(ST::query(p+1,mid) >= len) // mid 与 pos 的 len 
      L = mid;
    else
      R = mid-1;
  }
  ans.second = L;
  // printf("ans:%d %d\n",ans.first,ans.second);
  return ans;
}


struct Query{
  int pos,l,r,op;// op 代表 +1 或者 -1
  int id;
};

vector<Query> Q; 

bool cmp(Query x,Query y){
  return x.pos < y.pos;
}

void solve(){
  // read the question
  BIT::init(n);
  for(int i = 1;i<=q;i++){
    int l,r,k;
    scanf("%d %d %d",&l,&r,&k);
    pair<int,int> tmp = getrange(st[k],str_len[k]);
    Q.push_back((Query){tmp.second,l,r, 1,i});
    Q.push_back((Query){tmp.first-1,l,r,-1,i});
  }
  sort(Q.begin(),Q.end(),cmp);
  int now = 0;
  static int ans[MAXN];
  for(unsigned i = 0;i < Q.size();i++){
    while(now < cnt+1 && now <= Q[i].pos){
      BIT::update(belong[SA::sa[now]],1);
      now++;
    }
    // printf("now:%d Q:%d %d %d %d %d\n",now,Q[i].pos,Q[i].l,Q[i].r,Q[i].id,Q[i].op);
    ans[Q[i].id] += Q[i].op * BIT::query(Q[i].l,Q[i].r);
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