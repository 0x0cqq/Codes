#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#define ll long long
using namespace std;

const int MAXN = 110000;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*s,*t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(s==t)t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);return s==t?-1:*s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

struct Q{
    bool w;
    int id,b,c;
    // id -> 加入时间 b -> 加入的位置 c -> 这个数的大小
    Q(int x,int y,int z):id(x),b(y),c(z){}
    Q(){}
    bool operator < (Q w)const{//用于排序
        if(id!=w.id) 
            return id < w.id;
        if(b!=w.b)
            return b < w.b;
        return c < w.c;
    }
}q[MAXN];

int n,m;
int num[MAXN],pos[MAXN],del[MAXN];
ll ans[MAXN];
// num -> 原数组
// pos -> 值对应的位置
// del -> 删除第 pos 个数的序顺 

namespace BIT{
    ll sumn[MAXN];
    int lowbit(int x){
        return x & (-x);
    }
    void add(int x,int d){
        while(x <= n) sumn[x] += d,x += lowbit(x);
    }
    ll query(int x){
        ll ans = 0;
        while(x >= 1) ans += sumn[x],x -= lowbit(x);
        return ans;
    }
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(num[i]);
        pos[num[i]] = i;
    }
    int tmp; 
    for(int i = 1;i<=m;i++){
        read(tmp);
        del[pos[tmp]] = i;
    }
}

int l,r,tot,tmp[MAXN];

inline bool judge(int x,int y){//判断归并顺序函数 这里因为不重复，可以不写其他维判定
    return q[x].b < q[y].b;
}


void CDQ(int *t,int num){
    if(num == 1) return;
    int mid = num/2;
    CDQ(t,mid),CDQ(t+mid,num-mid);//分治解决问题
    //进行归并
    for(l=0,r=mid,tot=0;tot < num;tot++){
        if((r==num)||(l<mid && judge(t[l],t[r])))//这一行的条件易错
            q[t[l]].w = 0,tmp[tot] = t[l++];
        else
            q[t[r]].w = 1,tmp[tot] = t[r++];
    }
    for(int i = 0;i<num;i++) t[i] = tmp[i];

    //统计id(time)比其小 b(pos)比其小 c(val)比其大的数的个数
    for(int i = 0;i<num;i++)
        if(!q[t[i]].w) BIT::add(q[t[i]].c,1);
        else ans[q[t[i]].id] += BIT::query(n)-BIT::query(q[t[i]].c);
    for(int i = 0;i<num;i++)
        if(!q[t[i]].w) BIT::add(q[t[i]].c,-1);
    //统计id(time)比其小 b(pos)比其大 c(val)比其小的数的个数
    for(int i = num-1;i>=0;--i)
        if(!q[t[i]].w) BIT::add(q[t[i]].c,1);
        else ans[q[t[i]].id] += BIT::query(q[t[i]].c-1);
    for(int i = num-1;i>=0;--i)
        if(!q[t[i]].w) BIT::add(q[t[i]].c,-1);
}

void solve(){
    int nowcnt = 0;
    static int tt[MAXN];
    for(int i = 1;i<=n;i++){
        //遍历每个pos 
        if(del[i] == 0) q[i] = Q(1,i,num[i]);
        else q[i] = Q(m-del[i]+2,i,num[i]);
    }
    sort(q+1,q+1+n);
    for(int i = 1;i<=n;i++)
        tt[i] = i;
    CDQ(tt+1,n);
    // 前缀和统计答案
    for(int i = 1;i<=m+1;i++)
        ans[i] += ans[i-1];
    for(int i = m+1;i>1;--i)
        print(ans[i]),print('\n');
}

int main(){

    init();
    solve();
    flush();
    return 0;
}