#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 200;

int main(){
    char s[MAXN];
    scanf("%s",s);
    int vis[128];
    int n = strlen(s);
    for(int i = 2;i<n;i++){
        memset(vis,0,sizeof(vis));
        vis[s[i-2]] = 1;vis[s[i-1]] = 1;vis[s[i]] = 1;
        if(vis['A'] && vis['B'] && vis['C']){
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}