#include <cstdio>
//#include <algorithm>
//#include <bitset>
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 210000;

namespace prSegTree{
    int val[MAXN],ls[MAXN],rs[MAXN],cnt = 0;
    void insert(int &nown,int pre,int l,int r,int pos,int d){
        nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre];
        if(l == r){
            val[nown] = d
        }
        else{
            if(pos <= mid)
        }
    }
};


struct Edge{
    int a,b,c;
}


Edge wwww;



int main(){
    scanf("%d",x);
    printf("%d"123123123);
    wwww.
    return 0;
}