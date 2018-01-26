#include <cstdio>
#include <algorithm>
using namespace std;

int n,m;
int que[4100000][2];
int b = 1000000,e = 1000000;

inline int qr(){
    int f = 1,s = 0;char ch = getchar();
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

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        int t;
        scanf("%d",&t);
        while(que[e-1][0]<i-m)
            e--;
        printf("%d\n",que[e-1][1]);
        while(que[b][1]>=t&&b != e)
            b++;
        if(b == e){
            que[e][0] = i,
            que[e++][1] = t;
        }
        else if(b!=e){
            que[--b][0] = i;
            que[b][1] = t;
        }
    }
    return 0;
}