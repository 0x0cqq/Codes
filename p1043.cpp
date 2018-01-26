#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

long long num[150],dp_1[150],dp_2[150];//_1放最大值,_2放最小值

int n,m;

inline int mod(long long nnn){//mod函数，不解释
    int w = int(floor(double(nnn)/10));
    return nnn - w*10;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){//断环为链的准备
        scanf("%lld",&(num[i]));
        num[i+n] = num[i];
    }
    for(int i = 1;i<=2*n;i++)//前缀和的处理
        num[i] = num[i-1]+num[i];
    
    //正经dp
    long long maxn = -1,minn = 1000000000000;
    for(int s = 1;s<=n;s++){//枚举起点
        memset(dp_1,0,sizeof(dp_1));//清零dp数组
        memset(dp_2,0,sizeof(dp_2));
        for(int j = 0;j<m;j++){//板子由少到多
            for(int i = s;i<=s+n;i++){//上一个插板子的地方
                if(j == 0){//j==0的时候的处理，其实也可以叫初始化
                    dp_1[i] = dp_2[i] = mod(num[s+n]-num[i]);
                    continue;
                }
                long long maxtmp = -1,mintmp = 1000000000000;//对所有可能下一状态的遍历，并取最大或最小值
                for(int x = i+1;x<=s+n-j-1;x++){
                    maxtmp = max(maxtmp,dp_1[x]*mod(num[x]-num[i]));
                    mintmp = min(mintmp,dp_2[x]*mod(num[x]-num[i]));
                }
                dp_1[i] = maxtmp;//取最大最小值
                dp_2[i] = mintmp;
            }
        }
        maxn = max(dp_1[s],maxn);//对于起点不同的最大最小值进行更新
        minn = min(dp_2[s],minn);
    }
    printf("%lld\n%lld\n",minn,maxn);//开心的输出结果
    return 0;
}