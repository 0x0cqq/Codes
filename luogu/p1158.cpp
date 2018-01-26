#include <cstdio>
#include <algorithm>
#define pint pair<int,int>
#define min(x,y) ((y) ^ (((x) ^ (y)) & -((x) < (y))))
#define max(x,y) ((x) ^ (((x) ^ (y)) & -((x) < (y))))

using namespace std;

int x1,y1,x2,y2,k;

pint p[110000];

inline bool cmp(pint a,pint b){
    /*int q = max(a.first,a.second),w = max(b.first,b.second);
    if(q!=w)
        return q>w;
    else
        return min(a.first,a.second)>min(b.first,b.second);
    */
    return a.first + a.second > b.first + b.second;
}

int main(){
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    scanf("%d",&k);
    for(int i = 0;i<k;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        p[i].first = (a-x1)*(a-x1)+(b-y1)*(b-y1);
        p[i].second = (a-x2)*(a-x2)+(b-y2)*(b-y2);
    }
    sort(p,p+k,cmp);
    int mina = 0,minb = 0;
    for(int i = 0;i<k;i++){
        if(p[i].first<=mina||p[i].second<=minb)
            continue;
        else{
            int ma = p[i].first-mina;
            int mb = p[i].second-minb;
            if(ma<mb){
                mina = p[i].first;
            }
            else{
                minb = p[i].second;
            }
        }
    }
    printf("%d\n",mina+minb);
    return 0;
}