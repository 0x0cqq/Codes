#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1110000;

int n,p = 1000000007;
int nex[MAXN],cnt[MAXN];
char s[MAXN];

int main(){
    scanf("%d",&n);
    for(int T = 1;T<=n;T++){
        scanf("%s",s);
        memset(nex,0,sizeof(nex));
        memset(cnt,0,sizeof(cnt));
        nex[0] = 0;
        int j = 0,j_1 = 0,len = strlen(s);
        long long ans = 1;
        for(int i = 1;i<len;i++){
            while(j > 0 && s[i]!=s[j])
                j = nex[j-1];
            if(s[i] == s[j]) ++j;
            nex[i] = j;
            cnt[i] = cnt[nex[i-1]]+1;
            //
            while(j_1 > 0 && s[i]!=s[j_1])
                j_1 = nex[j_1-1];
            if(s[i] == s[j_1]) ++j_1;
            while(j_1>0 && (j_1<<1) > i+1)
                j_1 = nex[j_1-1];
            ans*=(cnt[j_1]+1),ans%=p;
        }
        printf("%lld\n",ans);
    }
    return 0;
}