#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <vector>
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n'&&c!='\r') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 51000,MAX = 1100000;

int n,m,Q;
int col[MAXN],re_col[MAXN],re_pos[MAXN],cnum = 1;
int l = 0,r = 0,x = 0;

int num[MAX],ans = 0;

struct Query{
    int id,ql,qr,qx,ans;
    bool operator < (Query b)const{
        if(ql/Q != b.ql/Q)
            return ql/Q < b.ql/Q;
        if(qr/Q != b.qr/Q) 
            return qr/Q < b.qr/Q;
        return qx < b.qx;
    }
};

bool cmp(Query a,Query b){
    return a.id < b.id;
}

vector<Query> query;

void init(){
    read(n),read(m);Q = sqrt(n*100);
    for(int i = 1;i<=n;i++)
        read(col[i]);
    for(int i = 1;i<=m;i++){
        char op[10];int a,b;
        read(op);read(a),read(b);
        if(op[0] == 'Q'){
            Query w;w.ql = a,w.qr = b,w.qx = cnum-1;
            w.id = i;query.push_back(w);
        }
        else if(op[0] == 'R'){
            re_pos[cnum] = a,re_col[cnum] = b;
            cnum++;
        }
    }
    sort(query.begin(),query.end());
}

void add(int pos){
    if(num[col[pos]]++ == 0)
        ans++;
}

void del(int pos){
    if(--num[col[pos]] == 0)
        ans--;
}

void change(int times){
    if(l<=re_pos[times]&& re_pos[times] <= r){
        if(num[re_col[times]]++ == 0)
            ans++;
        if(--num[col[re_pos[times]]] == 0)
            ans--;
    }
    swap(re_col[times],col[re_pos[times]]);
}

void solve(){
    for(int i = 0;i<query.size();i++){
        Query w = query[i];
        while(l > w.ql)  add(--l);
        while(r < w.qr)  add(++r);
        while(l < w.ql)  del(l++);
        while(r > w.qr)  del(r--);
        while(x < w.qx)  change(++x);
        while(x > w.qx)  change(x--);
        query[i].ans = ans;
    }
    sort(query.begin(),query.end(),cmp);
    for(int i = 0;i<query.size();i++)
        print(query[i].ans),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}