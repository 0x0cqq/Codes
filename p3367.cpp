#include <cstdio>
using namespace std;

int n,m,p[10000];

inline int find(int x){
    int t = x;
    while(p[t]!=t){
        t = p[t];
    }
    while(p[x]!=x){
        int tem = p[x];
        p[x] = t;
        x = tem;
    }
    return t;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++)
        p[i] = i;
    for(int i = 0;i<m;i++){
        int f,a,b;
        scanf("%d %d %d",&f,&a,&b);
        int x = find(a),y = find(b);
        if(f == 1)
            p[x] = y;
        else{
            if(x == y)
                putchar('Y');
            else
                putchar('N');
            putchar('\n');
        }
    }
    return 0;
}