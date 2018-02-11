/* 
    Luogu p1196
    2018-02-10 20:39:04
    136ms, 2070KB
*/

#include <cstdio>
#include <algorithm>
#define MAXN 30010
using namespace std;

int f[MAXN],d[MAXN],s[MAXN],t;

int find(int x){
    if(f[x] == x){
        return x;
    }
    else{
        int w = find(f[x]);
        d[x] += d[f[x]];
        f[x] = w;
        return w;
    }
}

void un(int x,int y){
    int b = find(y),e = find(x);
    if(b == e) return;
    else{
        d[e] = s[b],d[b] = 0;
        s[b] = s[b] + s[e],s[e] = 0;
        f[e] = b;
        return;
    }
}

int main(){
    scanf("%d",&t);
    for(int i = 1;i<MAXN;i++){
        f[i] = i,d[i] = 0,s[i] = 1;
    }
    for(int i = 1;i<=t;i++){
        char op[20];int a,b;
        scanf("%s",op);
        scanf("%d %d",&a,&b);
        if(op[0] == 'M'){
            un(a,b);
        }
        else{
            int a1 = find(a),b1 = find(b);
            if(a1!=b1){
                printf("-1\n");
            }
            else{
                printf("%d\n",abs(d[a]-d[b])-1);
            }
        }
    }
    return 0;
}