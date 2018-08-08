#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;

const int MAXN = 512;

int n,k;

vector<int> V;

vector<int> MAX[MAXN*1000];int cnt,nowmax;

bitset<MAXN> ans[MAXN];


void dfs(int left){
    for(int j = 1;j<=left;j++){
        for(int i = 0;i<V.size();i++){
            ans[j] |= (ans[j-1] << V[i]);
            ans[j][V[i]] = 1;
        }       
    }
}

int getans(){
    for(int i = 0;i<5;i++)
        ans[i].reset();
    ans[0][0] = 1;
    dfs(n);
    // for(int j = 1;j<=n;j++){
    //     printf("j:%d\n",j);
    //     for(int i = 1;i<20;i++){
    //         printf("    %d:%d\n",i,int(ans[j][i]));
    //     }
    // }
    for(int i = 1;i<=512;i++){
        if(!ans[n][i])
            return i-1;
    }
    return 0;
}

vector<int> tt;

pair<int,int> cal(int left,int now){
    if(left == 0){
        int t = getans();
        // printf("V:\n");
        // for(int i = 0;i<V.size();i++){
        //     printf("%d ",V[i]);
        // }
        // printf("\n");
        // printf("ANS:%d\n",t);
        if(t > nowmax){
            MAX[++cnt] = V;
            return make_pair(t,cnt);
        }
        else{
            return make_pair(0,0);
        }
    }
    pair<int,int> ans = make_pair(0,0);
    for(int i = now+1;i<=128;i++){
        V.push_back(i);
        ans = max(ans,cal(left - 1,i));    
        V.pop_back();
    }
    return ans;
}

int main(){
    scanf("%d %d",&n,&k);
    V.push_back(1);--k;
    pair<int,int> aa = cal(k,1);
    for(int i = 0;i<MAX[aa.second].size();i++){
        printf("%d ",MAX[aa.second][i]);
    }
    printf("\n");
    printf("MAX=%d\n",aa.first);
    return 0;
}