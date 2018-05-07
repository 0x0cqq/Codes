#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 210000;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%lld",&x);}
    inline void print(int x){printf("%lld",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

int n,m;
int num[MAXN];
int a[MAXN];
 

signed main(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(a[i]);
    for(int i = 1;i<=n;i++)
        num[i] = num[i-1] + a[i];
    int nowr = 0,t;
    for(int i = 1;i<=m;i++){
        read(t);
        nowr += t;
        int nowp = upper_bound(num+1,num+n+1,nowr)-num-1;
        if(nowp == n) nowp = 0,nowr = 0;
        print(n-nowp),print('\n');
    }
    return 0;
}