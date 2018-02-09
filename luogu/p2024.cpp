#include <cstdio>
using namespace std;


int f[51000],r[51000],n,k,cnt = 0;//0代表同类 1代表吃父亲 2代表被父亲吃

inline void qr(int &x){
    x = 0;char ch = getchar();
    while(ch<'0'||ch>'9')
        ch = getchar();
    while(ch>='0'&&ch<='9'){
        x = (x<<3)+(x<<1)+ch-48;ch = getchar();
    }
}

inline int find(int x){
    if(f[x]!=x){
        int w = find(f[x]);
        r[x] = (r[x]+r[f[x]])%3;
        f[x] = w;
    }
    return f[x];
}

inline bool un(int x,int y,int re){//0代表同类，1代表x吃y
    int x1 = find(x),y1 = find(y);
    if(x1 == y1){
        if((r[x]-r[y]+3)%3!=re) return 1;
    }
    else{
        re = (re+r[y]-r[x]+3)%3;
        f[x1] = y1;r[x1] = re;
    }
    return 0;
}

int main(){
    qr(n);qr(k);
    for(int i = 1;i<=n;i++)
        f[i] = i;
    while(k--){
        int a,b,c;
        qr(a);qr(b);qr(c);
        if(b>n||c>n) ++cnt;
        else if(un(b,c,a-1))
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}