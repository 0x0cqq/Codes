#include <cstdio>
#include <algorithm>
#include <vector>
#define pp pair<int,int>
#define pos first
#define col second
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXM = 100;

int n,k;

int cnt[MAXM],sum = 0;

vector<pp> T;

int main(){
    scanf("%d %d",&n,&k);
    for(int i = 1;i<=k;i++){
        int t,w;
        read(t);
        for(int j = 1;j<=t;j++){
            read(w);
            T.emplace_back(w,i);
        }
    }
    sort(T.begin(),T.end());
    int l = 0,r = 0,ans = 0x3f3f3f3f;
    int last = 0;
    // for(auto W:T)
    //     printf("%d:%d\n",W.pos,W.col);
    while(r < T.size()){
        // printf("%d %d\n",l,r);
        // for(int i = 1;i<=k;i++)
        //     printf("%d ",cnt[i]);
        // printf("\n");
        if(cnt[T[r].col]++ == 0) sum++;
        r++;

        while(true){
            if(cnt[T[l].col]-1 != 0){
                cnt[T[l].col]--;
                l++;
            }
            else
                break;
        }
        if(sum == k) ans = min(ans,T[r-1].pos - T[l].pos);
    }
    printf("%d\n",ans);
    return 0;
}