#include <cstdio>
#include <vector>
#include <algorithm>
#define int  long long
using namespace std;

const int MAXN = 3100;

int n,m;
int p[MAXN],c[MAXN];

vector<int> V[MAXN],VV;

bool cmp(int a,int b){
    return a > b;
}

signed main(){
    scanf("%lld %lld",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld %lld",&p[i],&c[i]);
    }
    int ans = 0x3f3f3f3f3f3f3f3f;
    for(int x = 1;x<=n;x++){
        int nowans = 0,num = 0;
        for(int i = 1;i<=m;i++)
            V[i].clear();
        for(int i = 1;i<=n;i++)
            V[p[i]].push_back(c[i]);
        for(int i = 1;i<=m;i++)
            sort(V[i].begin(),V[i].end(),cmp);
        num = V[1].size();
        VV.clear();
        for(int i = 2;i<=m;i++){
            while(V[i].size() > x-1){
                nowans += V[i].back();
                num++;
                V[i].pop_back();
            }
            for(int j = 0;j<V[i].size();j++){
                VV.push_back(V[i][j]);
            }
        }
        
        sort(VV.begin(),VV.end(),cmp);
        while(num < x){
            nowans += VV.back();
            num++;
            VV.pop_back();           
        }
        // printf("%lld:%lld\n",x,nowans);
        ans = min(ans,nowans);
    }
    printf("%lld\n",ans);
    return 0;
}