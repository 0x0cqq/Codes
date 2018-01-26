#include <cstdio>
#include <cmath>
#define max(a,b) ((a)>(b)?(a):b)
using namespace std;

int maxn[100010][20];

int n,m;

int bin[20];

void prepare(){
    int t = 0;
    for(int i = 0;;i++,t++){
        bin[i] = pow(2,i);
        if(bin[i]>n) break;
    }
    for(int j = 1;j<=t;j++)
        for(int i = 1;i<=n;i++){
            if(i+bin[j-1]<=n)
                maxn[i][j] = max(maxn[i][j-1],maxn[i+bin[j-1]][j-1]);
            else
                maxn[i][j] = maxn[i][j-1];
        }
}

int query(int l,int r){
    int t = 1,x = 0;
    while((t<<1)<=r-l+1){
        t<<=1;
        x++;
    }
    return max(maxn[l][x],maxn[r-t+1][x]);
}

int main(){
    scanf("%d %d\n",&n,&m);
    for(int i = 1;i<=n;i++)
        scanf("%d",&maxn[i][0]);
    prepare();
    for(int i = 1;i<=m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",query(a,b));
    }
    return 0;
}