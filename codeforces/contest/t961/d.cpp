#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define pp pair<int,int>
using namespace std;

vector<pp > p;

int n,is[200][200][200];

void init(){
    srand(time(NULL));
    scanf("%d",&n);
    int x,y;
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&x,&y);
        p.push_back(make_pair(x,y));
    }
}

inline bool judge(pp a,pp b,pp c){
    if(!(a.second==c.second&&a.second==b.second))
        return (a.first-b.first)*(a.second-c.second) == (a.first-c.first)*(a.second-b.second);
    else{
       return a.second == b.second && b.second == c.second; 
    }
}

void solve2(){
    int x,y;
    for(int xxx = 1;xxx<=10;xxx++){
        for(int i = 1;i<=n*10;i++){
            x = rand()%n,y = rand()%n;
            swap(p[x],p[y]);
        }
        pp a = p[0],b = p[1],c = p[2];
        for(int i = 3;i<n;i++){
            printf("%d %d\n",p[i].first,p[i].second);
            if(judge(a,b,p[i]) == 0 && judge(b,c,p[i]) == 0 && judge(c,a,p[i] ) == 0){
                printf("NO\n");
                return;
            }
        }
    }
    printf("YES\n");
}

int main(){
    init();
    if(n<=4){
        printf("YES\n");
    }
    else{
        solve2();
    }
    return 0;
}