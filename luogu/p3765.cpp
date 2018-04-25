#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 550000;

int n,m,num[MAXN];

namespace Treap{
    int nowcnt = 0;
    int p[MAXN],son[MAXN][2];
    int siz[MAXN];
    int root[MAXN];
    void update(int x){
        siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
    }
    void rotate(int &x,int t){
        int y = son[x][t];
        son[x][t] = son[y][1-t];
        son[y][1-t] = x;
        update(x),update(y);
        x = y;
    }
    void insert(int &x,int v){
        if(!x){
            x = v,p[x] = rand();
        }
        else{
            int t = v > x;
            insert(son[x][t],v);
            if(p[son[x][t]] < p[x])
                rotate(x,t);
        }
        update(x);
    }
    void erase(int &x,int v){
        if(x == v){
            if(!son[x][0] && !son[x][1]){
                x = 0;return;
            }
            int t = p[son[x][0]] > p[son[x][1]];
            rotate(x,t);
            erase(x,v);
        }
        else{
            if(x == 0){
                printf("!!!\n");
                return;
            }
            erase(son[x][v > x],v);
        }
        update(x);
    }
    int grank(int r,int v){
        int x = r,ans = 0;
        while(x){
            if(v < x)
                x = son[x][0];
            else if(v == x)
                ans += siz[son[x][0]],x = 0;
            else
                ans += siz[son[x][0]]+1,x = son[x][1]; 
        }
        return ans;
    }
    void __print(int x,int dep){
        if(dep == 0)
            printf("%d:-------------------\n",x);
        if(x == 0) return;
        __print(son[x][0],dep+1);
        for(int i = 0;i<dep;i++) putchar(' ');
        printf("v:%d p:%d siz:%d son:%d %d\n",x,p[x],siz[x],son[x][0],son[x][1]);
        __print(son[x][1],dep+1);
        if(dep == 0)
            printf("---------------------\n");
    }
    bool check(int num,int l,int r){
        //if(l == 7392)
        //printf("num:%d l:%d r:%d res:%d-%d\n",num,l,r,grank(root[num],r+1),grank(root[num],l));
        return 2*(grank(root[num],r+1)-grank(root[num],l)) > r-l+1;
    }
    void update(int pos,int last,int now){
        //__print(root[last],0);
        //__print(root[now],0);
        erase(root[last],pos);
        insert(root[now],pos);
    }
    void init(int *a){
        p[0] = 2147483647;
        for(int i = 1;i<=n;i++){
            insert(root[a[i]],i);
        }
    }
}

namespace seg_tree{
    #define lson (nown<<1)
    #define rson ((nown<<1)|1)
    #define mid ((l+r)>>1)
    #define pp pair<int,int>
    #define fr first
    #define sc second
    pp tree[MAXN<<2];
    pp merge(pp a,pp b){
        pp ans;
        if(a.fr == b.fr)
            ans.fr = a.fr,ans.sc = a.sc + b.sc;
        else{
            ans.fr = a.sc > b.sc?a.fr:b.fr;
            ans.sc = a.sc - b.sc;
            if(ans.sc < 0) ans.sc *= -1;
        }
        return ans;
    }
    void update(int nown){
        tree[nown] = merge(tree[lson],tree[rson]);
    }
    void build(int nown,int l,int r,int *a){
        if(l == r){
            tree[nown] = make_pair(a[l],1);
            return;
        }
        build(lson,l,mid,a);
        build(rson,mid+1,r,a);
        update(nown);
    }
    pp query(int nown,int l,int r,int ql,int qr){
        if(ql <= l && r <= qr){
            return tree[nown];
        }
        else{
            pp ans;
            if(ql <= mid && mid+1 <= qr)
                ans = merge(query(lson,l,mid,ql,qr),query(rson,mid+1,r,ql,qr));              
            else if(ql <= mid)
                ans = query(lson,l,mid,ql,qr);
            else if(mid+1 <= qr)
                ans = query(rson,mid+1,r,ql,qr);
            return ans;
        }
    }
    void update(int nown,int l,int r,int pos,int val){
        if(l == r){
            tree[nown] = make_pair(val,1);
        }
        else{
            if(pos<=mid)
                update(lson,l,mid,pos,val);
            if(pos>=mid+1)
                update(rson,mid+1,r,pos,val);
            update(nown);
        }
    }
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(num[i]);
    }
    seg_tree::build(1,1,n,num);
    Treap::init(num);
}

void solve(){
    int l,r,s,k,t,win;
    //for(int i = 1;i<=n;i++){
    //    Treap::__print(Treap::root[i],0);
    //}
    for(int i = 1;i<=m;i++){
        read(l),read(r),read(s),read(k);
        if(l == r && l == 0){
            for(int i = 1;i<=n;i++){
                Treap::__print(Treap::root[i],0);
            }
            --i;continue;
        }
        win = seg_tree::query(1,1,n,l,r).first;
        win = Treap::check(win,l,r)? win:s;
        //printf("win:%d\n",win);
        for(int i = 1;i<=k;i++){
            read(t);
            Treap::update(t,num[t],win);
            seg_tree::update(1,1,n,t,win);
            num[t] = win;
        }
        print(win),print('\n');
    }
    win = seg_tree::query(1,1,n,1,n).first;
    win = Treap::check(win,1,n)?win:-1;
    print(win),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}