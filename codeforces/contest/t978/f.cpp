#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 210000;

int last[MAXN];
int n,m,num[MAXN];
int add[MAXN];
map<int,int> S;

namespace BIT{
    int sum[MAXN];
    int lowbit(int x){return x &(-x);}
    int query(int pos){
        int ans = 0;
        while(pos>=1){
            ans += sum[pos];
            pos -= lowbit(pos);
        }
        return ans;
    }
    void update(int pos,int d){
        while(pos<=n){
            sum[pos] += d;
            pos += lowbit(pos);
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
        S[num[i]] = 0;
    }
    int tmp = 0;
    for(auto it = S.begin();it!=S.end();it++){
        it->second = ++tmp;
        //printf("%d %d\n",it->first,it->second);
    }
    int a,b;
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&a,&b);
        if(num[a] > num[b])
            add[a] -= 1;
        else if(num[b]>num[a])
            add[b] -= 1;
    }
    for(int i = 1;i<=n;i++){
        BIT::update(S[num[i]],1);
    }
    for(int i = 1;i<=n;i++){
        printf("%d ",BIT::query(S[num[i]]-1)+add[i]);
    }
    printf("\n");
    return 0;
}