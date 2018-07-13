#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 400000;


int n;
int num[MAXN];
int tmp[MAXN];

int main(){
    scanf("%d",&n);
    num[0] = 1;
    int ans = 0;
    for(int i = 1;i<=1000;i++){
        ans = 0;
        memset(tmp,0,sizeof(tmp));
        for(int j = 0;j<=50*i;j++){
            if(num[j]){
                tmp[j+1] = 1;
                tmp[j+5] = 1;
                tmp[j+10] = 1;
                tmp[j+50] = 1;
            }
            if(tmp[j])
                ans++;
        }
        if(n == i){
            printf("%d",ans);
            return 0;
        }
        memcpy(num,tmp,sizeof(tmp));
    }
    printf("%lld\n",1LL*(n-1000)*49+ans);
    return 0;
}