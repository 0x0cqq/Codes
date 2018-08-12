// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>

#define MAXN 2000005

using namespace std;

int N, M;
int siz;
int ans = 0;
int qcnt, ccnt;
int cnt[MAXN];
int res[MAXN];
int a[MAXN], block[MAXN];

struct que
{
    int l, r, pre, id;
    bool operator < (const que &b) const
    {
        if(block[l] != block[b.l])
            return block[l] < block[b.l];	
        if(block[r] != block[b.r])
            return block[r] < block[b.r];
        return pre < b.pre;
    }
}Q[MAXN];

struct change
{
    int pos, val;
}C[MAXN];

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


inline void add(int v)
{
    if(++cnt[v] == 1)
        ans++;
}

inline void del(int v)
{
    if(--cnt[v] == 0)
        ans--;
}

inline void modify(int cur, int i)
{
    if(C[cur].pos >= Q[i].l && C[cur].pos <= Q[i].r)
    {
        if(--cnt[a[C[cur].pos]] == 0)
            ans--;
        if(++cnt[C[cur].val] == 1)
            ans++;
    }
    swap(C[cur].val, a[C[cur].pos]);
}

void init()
{
    read(N), read(M);
//	siz = sqrt(N);
    for(int i = 1; i <= N; i++)
    {
        read(a[i]);
//		block[i] = (i - 1) / siz + 1;
    }
    while(M--)
    {   
        char opt[10];
        read(opt);
        if(opt[0] == 'Q')
        {
            read(Q[++qcnt].l);
            read(Q[qcnt].r);
            Q[qcnt].pre = ccnt;
            Q[qcnt].id = qcnt;
        }
        else
        {
            read(C[++ccnt].pos);
            read(C[ccnt].val);
        }
    }
//	siz = ceil(exp(log(N) + log(ccnt) / 3));
    siz = sqrt(N*200);
//	siz *= 10;
    for(int i = 1; i <= N; i++)
        block[i] = (i - 1) / siz + 1;
    sort(Q + 1, Q + qcnt + 1);
}

void MoQuery()
{
    int L = 1, R = 0, cur = 0;
    for(int i = 1; i <= qcnt; i++)
    {
        while(L > Q[i].l) add(a[--L]);
        while(R < Q[i].r) add(a[++R]);
        while(L < Q[i].l) del(a[L++]);
        while(R > Q[i].r) del(a[R--]);
        while(cur < Q[i].pre) modify(++cur, i);
        while(cur > Q[i].pre) modify(cur--, i);
        res[Q[i].id] = ans;
    }
    for(int i = 1; i <= qcnt; i++)
        print(res[i]),print('\n');
}

int main()
{
    init();
    MoQuery();
    flush();
    return 0;
}