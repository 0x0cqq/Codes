#include <cstdio>
#include <cctype>
#define int long long
#define ll long long
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
#pragma GCC optimize(3)
using namespace std;

namespace fast_io {
    inline char read();
    inline void read(int&);
//  inline void read(char*);
    inline void print(char);
    inline void print(int);
//  inline void print(char*);
    inline void flush();
    inline char read() {
//		return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))== s)?-1:*s++) : *s++;
    }
    inline void read(int &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            	x = ((x+(x<<2))<<1) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c =='\n')){
            c = read();
        }
        while(c!= -1&&c!=' '&&c!='\n'){
            *a++ = c;
            c = read();
        }
        *a = 0;
    }*/
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x) {
        static int buf[30], cnt;
        if (x == 0) {
            print('0');
        }
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    /*
    inline void print(char *a){
        while(*a) print(*a++);
    }
    */
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

ll addn[500000],chengn[500000],sumn[500000];
ll n,m,p;

void pushup(int nown){
    sumn[nown] = (sumn[lson]+sumn[rson])%p;
}

void pushdown(int nown,int l,int r){
    if(chengn[nown]!=1){
        chengn[lson]*=chengn[nown];chengn[rson]*=chengn[nown];
        addn[lson]*=chengn[nown];addn[rson]*=chengn[nown];
        sumn[lson]*=chengn[nown];sumn[rson]*=chengn[nown];
        chengn[nown] = 1;
    }
    if(addn[nown]!=0){
        addn[lson] += addn[nown];addn[rson] += addn[nown];
        sumn[lson] += addn[nown]*(mid-l+1);
        sumn[rson] += addn[nown]*(r-mid);
        addn[nown] = 0;
    }
    chengn[lson]%=p;chengn[rson]%=p;
    addn[lson]%=p;addn[rson]%=p;
    sumn[lson]%=p;sumn[rson]%=p;
}

void build(int nown,int l,int r){
    addn[nown] = 0;chengn[nown] = 1;
    if(l == r){
        read(sumn[nown]);
        sumn[nown] %= p;
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(nown);
}

void update(ll val,int nown,int l,int r,int ql,int qr,bool optn){
    if(l>qr||r<ql)
        return;
    if(ql<=l&&r<=qr){
        if(optn){
            addn[nown]+= val;
            sumn[nown]+= val*(r-l+1);
        }
        else{
            addn[nown]*=val;chengn[nown]*=val;
            sumn[nown]*=val;
        }
        chengn[nown]%=p;addn[nown]%=p;sumn[nown]%=p;
        return;
    }
    pushdown(nown,l,r);
    if(ql<=mid)
        update(val,lson,l,mid,ql,qr,optn);
    if(mid+1<=qr)
        update(val,rson,mid+1,r,ql,qr,optn);
    pushup(nown);
}

ll query(int nown,int l,int r,int ql,int qr){
    if(l>qr||r<ql)
        return 0;
    if(ql<=l&&r<=qr){
        return sumn[nown] % p;
    }
    pushdown(nown,l,r);
    ll ans = 0;
    if(ql<=mid)
        ans+=query(lson,l,mid,ql,qr);
    if(mid+1<=qr)
        ans+=query(rson,mid+1,r,ql,qr);
    return ans%p;
}


main(){
    read(n),read(p);
    build(1,1,n);
    read(m);
    for(int i = 0;i<m;i++){
        ll a,b,c,d;
        read(a);read(b),read(c);
        if(a == 1){
            read(d);
            update(d,1,1,n,b,c,0);
        }
        else if(a == 2){
            read(d);
            update(d,1,1,n,b,c,1);
        }
        else if(a == 3){
            print(query(1,1,n,b,c)),print('\n');
        }
    }
    flush();
    return 0;
}