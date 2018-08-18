#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = 6,m = 2,t = 5,MAXN = 10;
    int x = rand()%n+1,y = rand()%m+1;
    printf("%d %d\n%d %d\n%d\n",n,m,x,y,t);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            printf("%d ",rand()%(2*MAXN)-MAXN);
        }
        printf("\n");
    }
    for(int i = 1;i<=t;i++){
        int op = rand()%2,x1,x2,y1,y2,v;
        printf("%d ",op);
        if(op == 0){
            x1 = rand()%(x),x2 = rand()%(n-x+1);
            y1 = rand()%(y),y2 = rand()%(m-y+1);
            printf("%d %d %d %d\n",x1,y1,x2,y2);
        }
        else{
            x1 = rand()%n+1,x2 = rand()%n+1;
            if(x1 > x2) swap(x1,x2);
            y1 = rand()%m+1,y2 = rand()%m+1;
            if(y1 > y2) swap(y1,y2);
            v = rand()%(2*MAXN)-MAXN;
            printf("%d %d %d %d %d\n",x1,y1,x2,y2,v);     
        }
    }
    return 0;
}