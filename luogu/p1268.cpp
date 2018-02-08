#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

short d[101][101],n;

int ans;

int main(){
    while(true){
        ans = 0;
        scanf("%d",&n);
        if(n == 0)
            break;
        for(int i = 1;i<=n;i++){
            for(int j = i+1;j<=n;j++){
                cin >> d[i][j];
                d[j][i] = d[i][j];
            }
        }
        ans+=d[1][2];
        for(int i = 3;i<=n;i++){
            int t = 0x3f3f3f3f;
            for(int w = 1;w<i;w++)
                for(int x = 1;x<i;x++)
                    t = min(int(d[w][i])+d[i][x]-d[w][x],t);
            t>>=1;ans+=t;
        }
        printf("%d\n",ans);
    }
    return 0;
}