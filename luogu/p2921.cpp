#include <cstdio>
#include <cstring>
#include <unistd.h>
using namespace std;


int n,next[110000],color[110000],times[110000];
bool v[110000];

int main(){
    freopen("1.in","r",stdin);
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&next[i]);
    }
    int c = 1;
    for(int i = 1;i<=n;i++){
        //memset(v,0,sizeof(v));
        printf("i:%d\n",i);
        if(color[i])
            printf("%d\n",times[color[i]]);
        else{
            int now = i,ans = 0;
            while(v[now] == 0){
                if(color[now]){
                    int nowt = i;
                    for(int j = ans;j>=1;j--){
                        times[c] = j + times[color[now]];
                        color[nowt] = c;
                        nowt = next[nowt];
                        c++;
                    }
                    printf("%d\n",ans+times[color[now]]);
                    break;
                }
                v[now] = 1;
                now = next[now];
                ans++;
            }
            printf("TTTEEEESSSSTTT!!!\n");
            printf("now:%d,color:%d\n",now,color[now]);
            if(color[now]==0){
                int tmp = now,tans = 1;
                color[tmp] = c;
                tmp = next[tmp];
                while(now!=tmp){
                    //usleep(100);
                    //printf("%d ",now);
                    color[tmp] = c;
                    tmp = next[tmp];
                    tans++;
                }
                times[c] = tans;
                printf("%d\n",ans);
                ans-=tans;
                c++;
                if(now!=i){
                    int nowt = i;
                    for(int j = ans;j>=1;j--){
                        times[c] = j + times[color[now]];
                        color[nowt] = c;
                        nowt = next[nowt];
                        c++;
                    }
                }
            }
            /*putchar('!');
            for(int i = 1;i<=n;i++){
                printf("%d ",color[i]);
            }
            putchar('\n'); 
            */ 
        }
    }
    return 0;
}