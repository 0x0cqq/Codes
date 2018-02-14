#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;

ll n,m;

namespace fast_IO {
    inline char read() {
//		return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),*s++:*s++;
    }
    inline void read(ll &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            x = (x + (x << 2) << 1) + (c ^ '0');
        if (iosig) x = -x;
    }
    const int OUT_LEN = 10000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(ll x) {
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
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_IO;

ll val[10001000],cha[10001000],ans1 = 0,ans2 = -1;


int main(){
    read(n);read(m);
    for(int i = 1;i<=m;i++){
        ll l,r,a,b,d;
        read(l),read(r),read(a),read(b);
        d = (b-a)/(r-l);
        val[l]+=a,val[r+1]-=b;
        cha[l]+=d,cha[r]-=d;
    }
    ll nown = 0,nowc = 0;
    for(int i = 1;i<=n;i++){
        nown+=val[i];
        nown+=nowc;
        nowc+=cha[i];
        ans1 ^= nown;ans2 = max(ans2,nown);
    }
    print(ans1),print(ans2);
    flush();
    return 0;
}