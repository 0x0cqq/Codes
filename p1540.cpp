#include <cstdio>
#include <cstring>
using namespace std;

int d[1000];

int main(){
    memset(d,1,4000);
    int n,m,b = 0,ans =0;
    scanf("%d %d",&m,&n);
    for(int i = 0;i<n;i++){
        int t;
        scanf("%d",&t);
        bool flag = 0;
        for(int i = b;i<m+b;i++){
            if(d[i]==t){
                flag = !flag;
                break;
            }
        }
        if(!flag){
            if(d[m+b-1]!=-1)
                d[m+(++b)-1]=t;
            else{
                for(int i = b;i<b+m;i++)
                    if(d[i]!=-1){
                        d[i]=t;
                        break;
                    }
            }
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}