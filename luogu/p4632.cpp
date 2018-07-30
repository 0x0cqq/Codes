#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define lson ls[x],l,mid
#define rson rs[x],mid+1,r
#define root rt,0,INF
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;if(s==t)t=(s=buf)+fread(buf,1,IN_LEN,stdin);return s==t?-1:*s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 310000,logn = 30,INF = 0x3f3f3f3f;

int n,m,k,q;
multiset<int> S[MAXN];// S 存储对于每一个K的位置

struct P{
    // 0 查询, 1 添加, -1 删除
    int op,x,t,k;
    bool operator < (const P &a)const{//add->query->del
        return t != a.t ? t < a.t : op > a.op;
    }
}w[MAXN<<2];

struct Heap{// 可删除任意元素的堆
    priority_queue<int,vector<int>,greater<int> > Q1,Q2;
    int size(){return Q1.size() - Q2.size();}
    void push(int v){Q1.push(v);}
    void pop(int v){Q2.push(v);}
    int top(){
        while(Q2.size() && Q1.top() == Q2.top()) 
            Q1.pop(),Q2.pop();
        return Q1.top();
    }
}H[MAXN];int pos[MAXN*logn],id;//对于每一个位置维护一个堆（动态分配）


//namespace SegTree{// 用左端点代表整个区间
int rt,ls[MAXN*logn],rs[MAXN*logn],minn[MAXN*logn],tot;
void update(int &x,int l,int r,int p,int u,int v){//u插入 v删除
    if(!x) x = ++tot;
    if(l == r){
        if(!pos[x]) pos[x] = ++id;
        Heap &h = H[pos[x]];
        if(~u) h.push(u);
        if(~v) h.pop(v);
        minn[x] = h.size()?h.top():INF;
    }
    else{
        if(p <= mid) update(lson,p,u,v);
        else update(rson,p,u,v);
        minn[x] = min(minn[ls[x]],minn[rs[x]]);
    }
}
int query(int p){
    int x = rt,l = 0,r = INF,ans = INF;//minn[0] = INF;
    while(l!=r){
        int tmp = min(ans,minn[rs[x]]);//tmp代表从mid+1开始的后缀最小值
        if(p <= mid && tmp + mid >= 2*p)
            r = mid,x = ls[x],ans = tmp;
        else
            l = mid+1,x = rs[x];
    }
    return l-p;
}
//}

void init(){
    static int x,t,a,b,l,y;
    read(n),read(k),read(q);
    for(int i = 1;i<=k;i++)
        S[i].insert(-INF),S[i].insert(INF),update(root,INF,-INF,-1);//整个区间都是-INF
    for(int i = 1;i<=n;i++){
        read(x),read(t),read(a),read(b);
        w[++m] = (P){1,x,a,t},w[++m] = (P){-1,x,b,t};
    }
    for(int i = 1;i<=q;i++){
        read(l),read(y);
        w[++m] = (P){0,l,y,i};
    }
    sort(w+1,w+m+1);
}

void solve(){
    minn[0] = INF;
    static int cnt,ans[MAXN];
    static multiset<int>::iterator rb,lb;
    for(int i = 1;i<=m;i++){
        P &p = w[i];
        if(p.op == 1){
            multiset<int> &s = S[p.k];
            rb = s.upper_bound(p.x),lb = rb--;
            // p.x 插入能够带来的变化区间：[*lb,*rb] 从lb到p.x的区间从*rb替换成p.x 从p.x之后的前驱继续是*rb
            update(root,*lb,p.x,*rb),update(root,p.x,*rb,-1);
            if(s.size() == 2) cnt++;
            s.insert(p.x);
        }
        if(p.op == -1){
            multiset<int> &s = S[p.k];
            s.erase(s.find(p.x));
            if(s.size() == 2) --cnt;
            rb = s.upper_bound(p.x),lb = rb--;
            update(root,*lb,*rb,p.x),update(root,p.x,-1,*rb);
        }
        if(p.op == 0)
            ans[p.k] = (cnt==k)?query(p.x):-1;
    }
    for(int i = 1;i<=q;i++)
        print(ans[i]),print('\n');
}


int main(){
    init();
    solve();
    flush();
    return 0;
}