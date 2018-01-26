#include <cstdio>
#include <cmath>
#include <iostream>
#define ll long long
#define mod(x) ((x)%d)
using namespace std;

ll qr(){
    ll f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    return f*s;
}

ll maxn[600000],m,d,len = 1,last = 0,k = 1;

void push_up(int nown){
    maxn[nown] = maxn[nown<<1]>maxn[nown<<1|1]?maxn[nown<<1]:maxn[nown<<1|1];
}

inline ll query(int l,int r){
    int ans = 0;
    for(l=k+l-1,r=k+r+1;l^r^1;l>>=1,r>>=1){
        if(~l&1)
            if(maxn[l^1]>ans)ans = maxn[l^1];
        if(r&1) 
            if(maxn[r^1]>ans)ans = maxn[r^1];
    }
    return ans;
}

inline void add(ll num){
    int pos = len+k;
    maxn[pos] = num;
    for(pos>>=1;pos;pos>>=1) push_up(pos);
    len++;
}

int main(){
    m = qr();d = qr();
    //getchar();
    while(k<m)
        k<<=1;
    for(int i = 0;i<m;i++){   
        char op = getchar();
        //printf(":%c\n",op);
        if(op == 'A'){
            ll n = qr();//getchar();
            n = mod(n+last);
            add(n);
        }
        else if(op == 'Q'){
            ll ql = qr();//getchar();
            if(ql == 0)
                last = 0;
            else
                last = query(len-ql,len-1);
            printf("%lld\n",last);
        }
    }
    return 0;
}