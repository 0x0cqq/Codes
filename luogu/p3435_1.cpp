#include <cstdio>
using namespace std;
#define int long long

const int MAXN = 1100000;

int n;
char s[MAXN];
int nex[MAXN],near[MAXN];

void get_next(){
    int j;j = nex[0] = 0;
    for(int i = 1;i<n;i++){
        while(j > 0 && s[i] != s[j])
            j = nex[j-1];
        if(s[i]==s[j]) j++;
        nex[i] = j;
    }
    // for(int i = 0;i<n;i++){
    //     printf("%d %d\n",i,nex[i]);
    // }
    j = 0;
    long long ans = 0;
    for(int i = 1;i<n;i++){
        j = i;
        while(j > 0 && (nex[j]-1)>=0)
            j = nex[j]-1;
        j++;
        if(j > 0 && j <= (i+1)/2)
            ans += (i+1)-j;
        // printf("i:%d j:%d\n",i,j);
    }
    printf("%lld\n",ans);
}

void init(){
    scanf("%d",&n);
    scanf("%s",s);
}

signed main(){
    init();
    get_next();
    return 0;
}
