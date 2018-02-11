#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 400010;

int f[MAXN],ans[MAXN],attack[MAXN],sur[MAXN],n,m,k;

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

int un(int a,int b){
    int a1 = find(a),b1 = find(b);
    if(a1 == b1||sur[a]||sur[b])
        return 0;
    else{
        f[a1] = b1;
        return 1;
    }
}

vector<int> edge[MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<n;i++){
        f[i] = i;
    }
    for(int i = 1;i<=m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    scanf("%d",&k);
    for(int i = 1;i<=k;i++){
        scanf("%d",&attack[i]);
        sur[attack[i]] = 1;
    }
    int cnt = 0;
    for(int i = 0;i<n;i++){
        if(sur[i] == 0){
            cnt++;
            for(auto w = edge[i].begin();w!=edge[i].end();w++){
                int to = *w;
                cnt -= un(i,to);
            }
        }
    }
    for(int i = k;i>=1;i--){
        ans[i] = cnt++;
        int nown = attack[i];
        sur[nown] = 0;
        for(auto w = edge[nown].begin();w!=edge[nown].end();w++){
            int to = *w;
            cnt -= un(nown,to);
        }
    }
    ans[0] = cnt;
    for(int i = 0;i<=k;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}