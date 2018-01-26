#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,f[1000];

inline int qr(){
    int f = 1,w = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        w = (w<<3)+(w<<1)+ch - 48;
        ch = getchar();
    }
    return f*w;
}

struct road{
    int x,y;
    int t;
    bool operator < (const road a)const{
        return t<a.t;
    }
}r[102000];


int find(int x){
    return f[x]==x?x:f[x] = find(f[x]);
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        r[i].x = qr();r[i].y = qr();r[i].t = qr();
    }
    sort(r,r+m);
    for(int i = 0;i<n;i++){
        f[i] = i;
    }
    for(int i = 0,tiao = 0;i<m;i++){
        int fx = find(r[i].x);
        int fy = find(r[i].y);
        if(fx == fy)
            continue;
        else{
            f[fx] = fy;
            tiao++;
            if(tiao == n-1){
                printf("%d\n",r[i].t);
                return 0;
            }
        }
    }
    printf("-1\n");
    return 0;
}