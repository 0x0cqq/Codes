#include <cstdio>
#include <cctype>
using namespace std;

int f[1000],n,m;

int find(int x){
    return f[x] == x?x:f[x]=find(f[x]);
}

int main(){
    while(true){
        scanf("%d",&n);
        if(n == 0) return 0;
        scanf("%d",&m);
        int ans = n-1;
        for(int i = 1;i<=n;i++)
            f[i] = i;
        for(int i = 0;i<m;i++){
            int a,b,x1,x2;
            scanf("%d %d",&a,&b);
            x1 = find(a),x2 = find(b);
            if(x1!=x2)
                ans--,f[x1] = x2;
        }
        printf("%d\n",ans);
    }
}