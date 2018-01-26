#include <cstdio>
#include <cstring>
using namespace std;

int z = 0,res[1000010],sss[1000010];
bool p[1000010];

void prime(){
    memset(p,1,1000010);
    for(int i = 2;i<=500000;i++){
        if(p[i]){
            int t = 2*i;
            while(t<=1000000){
                p[t] = 0;
                t+=i;
            }
        }
    }
    for(int i = 2;i<=1000000;i++){
        if(p[i])
            res[z++] = i;
    }
}

int cal(int h,int now){
    int w = h;
    if(sss[h])
        return sss[h];
    int ans = 1;
    while(w>=res[now]){
        if(w%res[now]==0){
            int temp = 0;
            while(w%res[now]==0){
                w /= res[now];
                temp++;
            }
            ans=cal(w,now+1)*(temp+1);
            break;
        }
        now++;
    }
    return sss[h] = ans;
}

int main(){
    prime();
    int n,ans = 0;
    scanf("%d",&n);
    if(n<=10000){
        for(int i = 1;i<=n;i++)
            ans+=cal(i,0);
    }
    else{
        for(int i = 1;i<=n;i++)
            ans+=(n/i);
    }
    printf("%d\n",ans);
    return 0;
}