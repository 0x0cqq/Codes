#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

char ch[MAXN];

int ans = 0,cnt = 0;

int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",ch);
    for(int i = 0;i<n+1;i++){
        if(ch[i] == 'x')
            cnt++;
        else{
            if(cnt >= 3){
                ans += cnt-2;
            }
            cnt = 0;
        }
    }
    printf("%d\n",ans);
    return 0;
}