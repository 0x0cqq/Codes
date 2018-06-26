#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000;

int n;
char a[MAXN],b[MAXN];

int main(){
    scanf("%s",a+1);
    scanf("%s",b+1);
    n = strlen(a+1);
    a[n+1] = 'X';
    b[n+1] = 'X';
    n++;
    int lastl = 0;//1,0
    int cnt = 0;
    int ans = 0;
    for(int i = 1;i<=n;i++){
        //printf("%d: %c %c %d\n",i,a[i],b[i],cnt);
        if(a[i] == 'X' && b[i] == 'X'){
            if(a[i-1] != 'X' && b[i-1] != 'X'){
                ans += cnt/3 * 2;
                if(cnt % 3 == 2 || (cnt%3 == 1 && lastl == 1))
                    ans++;  
            }
            // else if(a[i-1] == 'X' || b[i-1] == 'X'){
            //     if(lastl == 1)
            //         ans += cnt/3 * 2 + cnt % 3;
            //     else
            //         ans += cnt/3 * 2 + cnt%3 == 1?1:0;
            // }
            lastl = 0;
            cnt = 0;
        }
        else if(a[i] == 'X' || b[i] == 'X'){
            if(lastl == 1)
                ans += cnt/3 * 2 + cnt % 3;
            else
                ans += cnt/3 * 2 + ((cnt%3 >= 1)?1:0);
            if(cnt % 3 == 1 && lastl == 0)
                lastl = 0;
            else
                lastl = 1;
            cnt = 0;
        }
        if(a[i] == '0' && b[i] == '0')
            cnt++;
    }
    printf("%d\n",ans);
    return 0;
}