#include <cstdio>
using namespace std;

int res[10][1100000];
int dd[1110000];

int cal(int n){
    if(dd[n]) return dd[n];
    if(n<10){
        return n;
    }
    else{
        int ans = 1,w = n;
        while(n!=0){
            int tmp = n%10;
            if(tmp!=0)
                ans*=tmp;
            n/=10;
        }
        return dd[w] = cal(ans);
    }
}


int main(){
    int q;
    scanf("%d",&q);
    for(int i = 1;i<=1000000;i++){
        int cc = cal(i);
        for(int j = 1;j<=9;j++){
            if(cc == j)
                res[j][i] = res[j][i-1]+1;
            else
                res[j][i] = res[j][i-1];
        }
    }
    for(int i = 1;i<=q;i++){
        int l,r,c;
        scanf("%d %d %d",&l,&r,&c);
        printf("%d\n",res[c][r]-res[c][l-1]);
    }
    return 0;
}