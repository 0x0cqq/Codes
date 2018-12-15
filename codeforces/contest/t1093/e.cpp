#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

namespace Splay{
    int val[MAXN*40],siz[MAXN*40],cnt[MAXN*40];
    int c[MAXN*40][2],f[MAXN*40];int tot;
    int newnode(int v = 0){
        val[++tot] = v;
        return tot;
    }
    void maintain(int x){
        if(!x) return;
        siz[x] = siz[c[x][0]] + siz[c[x][1]] + cnt[x];
    }
    void rotate(int x,int &root){
        int y = f[x],z = f[y],t =(c[y][1]==x),w = c[x][1-t];
        if(z) c[z][c[z][1]==y] = x;
        c[x][1-t] = y,c[y][t] = w;
        if(w) f[w] = y;
        f[y] = x;f[x] = z;
        maintain(y),maintain(x);
        if(!f[x]) root = x;
    }
    void splay(int x,int &root,int target = 0){
        if(!x) return;
        while(f[x]!=target){
            int y = f[x],z = f[y];
            if(z!=target){
                (c[y][1]==x)^(c[z][1]==y)?rotate(x,root):rotate(y,root);
            }rotate(x,root);
        }
    }
    int find(int v,int &root){
        int x = root;
        while(x && val[x]!=v)
            x = c[x][val[x] < v];
        splay(x,root);
        return x;
    } 
    int __qrank(int r,int &root){
        int x = root;
        while(x){
            if(r <= siz[c[x][0]])
                x = c[x][0];
            else if(r <= siz[c[x][0]] + cnt[x])
                break;
            else
                r-=(siz[c[x][0]] + cnt[x]),x = c[x][1];
        }
        splay(x,root);
        return x;
    }
    int getrank(int v,int &root){
        int x = root,ans = 0;
        while(x && val[x] != v){
            if(v < val[x])
                x = c[x][0];
            else
                ans += siz[c[x][0]]+cnt[x],x = c[x][1];
        }
        ans += siz[c[x][0]]+1;splay(x,root);
        return ans;
    }
    int loworup(int v,int t,int &root){
        int x = root,ans = 0;
        while(x){
            int f = t?val[x] > v:val[x] < v;
            if(f) ans = x;
            x = c[x][t?1-f:f];
        }
        return ans;
    }
    void insert(int v,int &root){
        int x = root,y = 0;
        while(x && val[x]!=v)
            siz[x]++,y = x,x = c[x][val[x] < v];
        if(x)  cnt[x]++,siz[x]++;
        else{
            x = newnode(v);
            if(y) c[y][val[y] < v] = x;
            f[x] = y;siz[x] = cnt[x] = 1;
            if(!f[x]) root = x;
        }
        splay(x,root);
    }
    void erase(int v,int &root){
        int x = find(v,root);
        splay(x,root);
        if(cnt[x] > 1) cnt[x]--,siz[x]--;
        else{
            int l = loworup(v,0,root),r = loworup(v,1,root);
            splay(l,root),splay(r,root,l);
            c[r][0] = 0;
            maintain(r),maintain(l);
        }
    }
    int qrank(int r,int &root){return val[__qrank(r,root)];}
    void __print(int x,int depth){
        if(depth == 0) printf("-----------------\n");
        if(!x) return;
        __print(c[x][0],depth+1);
        for(int i = 0;i<depth;i++) putchar(' ');
        printf("%d: val:%d siz:%d(cnt:%d) c:%d %d f:%d\n",x,val[x],siz[x],cnt[x],c[x][0],c[x][1],f[x]);
        __print(c[x][1],depth+1);
        if(depth == 0) printf("-----------------\n");
    }    
    void print(int root){
        __print(root,0);
    }
}

namespace SegTree{
  int rt[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void del(int nown,int l,int r,int pos,int v){
    if(l == r){
      Splay::erase(v,rt[nown]);
    }
    else{
      Splay::erase(v,rt[nown]);
      if(pos <= mid) del(lson,l,mid,pos,v);
      if(pos >= mid + 1) del(rson,mid+1,r,pos,v);
    }
  }
  void insert(int nown,int l,int r,int pos,int v){
    if(l == r){
      Splay::insert(v,rt[nown]);
    }
    else{
      Splay::insert(v,rt[nown]);
      if(pos <= mid) insert(lson,l,mid,pos,v);
      if(pos >= mid+1) insert(rson,mid+1,r,pos,v);
    }
  }
  int a,b;
  void query(int nown,int l,int r,int ql,int qr,int &ans){
    if(ql <= l && r <= qr){
      // Splay::print(rt[nown]);
      // printf("q:%d %d\n",a,b);
      ans += (Splay::getrank(b+1,rt[nown]) - Splay::getrank(a,rt[nown]));
    }
    else{
      if(ql <= mid) query(lson,l,mid,ql,qr,ans);
      if(qr >= mid+1) query(rson,mid+1,r,ql,qr,ans);
    }
  }
}

int n,m;
int a[MAXN],b[MAXN];
int posa[MAXN],posb[MAXN];

void init(){
  read(n),read(m);
  for(int i = 1;i<=n;i++){
    read(a[i]);
    posa[a[i]] = i;
  }
  for(int i = 1;i<=n;i++){
    read(b[i]);
    posb[b[i]] = i;
  }
}


void build(){
  for(int i = 1;i<=(n<<2);i++){
    Splay::insert(-0x3f3f3f3f,SegTree::rt[i]);
    Splay::insert(0x3f3f3f3f,SegTree::rt[i]);
  }
  for(int i = 1;i<=n;i++){
    SegTree::insert(1,1,n,i,posb[a[i]]);
  }
}

void solve(){
  for(int i = 1;i<=m;i++){
    int op,la,lb,ra,rb,x,y;
    read(op);
    if(op == 1){
      read(la),read(ra),read(lb),read(rb);
      SegTree::a = lb,SegTree::b = rb;
      int ans = 0;
      SegTree::query(1,1,n,la,ra,ans);
      printf("%d\n",ans);
    }
    else{
      read(x),read(y);
      int numa = b[x],numb = b[y];
      // printf("num:%d %d %d %d\n",numa,posa[numa],numb,posa[numb]);
      SegTree::del(1,1,n,posa[numa],x),SegTree::del(1,1,n,posa[numb],y);
      SegTree::insert(1,1,n,posa[numa],y),SegTree::insert(1,1,n,posa[numb],x);
      posb[b[x]] = y,posb[b[y]] = x;
      swap(b[x],b[y]);
    }
  }
}



int main(){
  init();
  build();
  solve();
  return 0;
}