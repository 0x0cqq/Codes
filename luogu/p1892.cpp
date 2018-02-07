#include <cstdio>
#include <algorithm>
#define pp pair<int,int>
using namespace std;

int f[1010],r[1010],n,m;

int find(int x){
    if(f[x] == x)
        return x;
    else{
        if(f[f[x]] == f[x]){
            r[x] ^= r[f[x]];
            f[x]  = f[f[x]];
        }
        else{
            int w = find(f[x]);
            r[x]^=r[f[x]];
            f[x] = f[f[x]];
        }
        return f[x];
    }
}
int ans;

void un(int x,int y,bool re){
    int x1 = find(x),y1 = find(y);
    if(x1 == y1) return;
    else{
        if(r[x1] == 1&&r[y1] == 1)
            ans -= 2;
        else if(!(r[x1] == 0 && r[y1] == 0 && re == 1))
            ans -= 1;
        f[x1] = y1;
        r[y1] = r[x1] || r[y1] || re;
        r[x1] = re;
    }
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        f[i] = i;
    }
    ans = n;
    scanf("%d",&m);
    for(int i = 0;i<m;i++){
        char s[20];int a,b;
        scanf("%s",s);
        scanf("%d %d",&a,&b);
        un(a,b,s[0] == 'E');
    }
    printf("%d\n",ans);
    return 0;
}