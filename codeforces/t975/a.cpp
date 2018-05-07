#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

int hhh(char* a){
    char *p = a;
    int ans = 0;
    while(*p != 0)
        ans = ans * 111 + *p,p++;
    return ans;
}

set<int> a;

int main(){
    int n;
    scanf("%d",&n);
    int ans = 0;
    for(int i = 1;i<=n;i++){
        char op[10000];
        scanf("%s",op);
        sort(op,op+strlen(op));
        *unique(op,op+strlen(op)) = 0;
        int t = hhh(op);
        if(!a.count(t))
            a.insert(t),ans++;
    }
    printf("%d\n",ans);
    return 0;
}