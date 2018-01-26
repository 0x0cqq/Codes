#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <cstring>
using namespace std;

int l[100],n,sum = 0,d[100],ge,len,v[100];

bool cmp(int a,int b){
    return a>b;
}

bool dfs(int now,int man,int ans){
    //usleep(100);
    //printf("ge: %d now:%d\n",ge,now);
    /*for(int i = 0;i<ge;i++){
        printf("%d ",d[i]);
    }
    putchar('\n');*/
    if(sum-ans<len)
        return false;
    bool b[1000];
    memset(b,0,sizeof(b));
    if(now >= n)
        return true;
    if(n-now<ge-man){
        return false;
    }
    int i;
    for(i = 0;d[i];i++){
        if(b[d[i]])
            continue;
        if(d[i]+l[now]<=len){
            b[d[i]] = 1;
            d[i]+=l[now];
            bool m = d[i]==len;
            if(dfs(now+1,man+m,ans+l[now]))
                return true;
            d[i]-=l[now];
        }
    }
    if(i<ge){
        d[i]+=l[now];
        bool m = d[i]==len;
        if(dfs(now+1,man+m,ans+l[now]))
            return true;
        d[i]-=l[now];
    }
    return false;
}

int main(){
    //freopen("1.in","r",stdin);
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int t;
        scanf("%d",&t);
        if(t>50){
            i--;n--;
        }
        else{
            l[i] = t;
            sum+=t;
        }
    }
    sort(l,l+n,cmp);
    for(int i = l[0]+l[n-1];i<=sum;i++){
        //printf("i: %d,sum: %d\n",i,sum);
        if(sum%i!=0)
            continue;
        ge = sum/i;
        len = i;
        if(dfs(0,0,0)){
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}