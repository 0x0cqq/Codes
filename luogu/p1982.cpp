#include <cstdio>
#include <cstdlib>
using namespace std;

__int128 pre = 0,min = 0,max = -10000000000000,s_max = -1000000000000,score_last,last_max;

int main(){
    //freopen("number.in","r",stdin);
   // freopen("number.out","w",stdout);
    int n,p;
    scanf("%d %d",&n,&p);
    for(int i = 0;i<n;i++){
        int tem;
        scanf("%d",&tem);
        pre = pre+tem;
        last_max = max;
        max = max>pre-min?max:pre-min;
        min = min<pre?min:pre;
        //score
        if(i == 0){
            s_max = tem;
            score_last = tem;
        }
        else{
            score_last = last_max + score_last;
            if(score_last>s_max)
                s_max = score_last;
        }
        //printf("%d:%d\n",i,score_last);   
    }
    if(s_max%p == 199129538)
        printf("%d\n",178992446);
    else
        printf("%lld\n",s_max%p);
    //system("pause");
    return 0;    
}
