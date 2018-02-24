#include <cstdio>
#include <cmath>
using namespace std;


int exgcd(int a,int b,int &x,int &y){
    if(b == 0){
        x = 1,y = 0;
        return a;
    }
    int ret = exgcd(b,a%b,x,y);
    int rex = y,rey = x - a/b * y;
    x = rex,y = rey;
    return ret;
}

int cal(int a,int b,int c,int &x,int &y){
    int d = exgcd(a,b,x,y);
    d*=(c/d),x*=(c/d),y*=(c/d);
    return d;
}

int a,b,x,y;

void init(){
    scanf("%d %d",&a,&b);
}

void solve(){
    int kkk = cal(a,b,1,x,y);
    int w = x%(b/kkk);
    if(w<0) w+=(b/kkk);
    printf("%d\n",w);
}

int main(){
    init();
    solve();
    return 0;
}