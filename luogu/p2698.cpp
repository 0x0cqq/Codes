#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100000;

struct pp{
    int x,y;
    pp(int a = 0,int b = 0):x(a),y(b){};
    bool operator < (const pp w)const{
        if(x!=w.x)
            return x < w.x;
        else
            return y < w.x;
    }
}dr[MAXN];

int n,d;

void init(){
    scanf("%d %d",&n,&d);
    int a,b;
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&a,&b);
        dr[i] = pp(a,b);
    }
    sort(dr+1,dr+n+1);
}


bool judge(int w){
    // printf("%d:\n",w);
    if(n == 1) return 0;
    deque<int> minn,maxn;
    int ta,tb;
    //minn.push_back(1);maxn.push_back(1);
    for(int i = 1;i<=n;i++){
        while(!minn.empty() && dr[minn.front()].x < dr[i].x - w)
            minn.pop_front();
        while(!minn.empty() && dr[minn.back()].y > dr[i].y)
            minn.pop_back();
        minn.push_back(i);
        if(!minn.empty())
            ta = dr[minn.front()].y;
        else
            ta = 0x3f3f3f3f;
        // printf("minn: ");
        // for(auto w:minn){
        //     printf("%d ",w);
        // }
        // printf("\n");


        while(!maxn.empty() && dr[maxn.front()].x < dr[i].x - w)
            maxn.pop_front();
        while(!maxn.empty() && dr[maxn.back()].y < dr[i].y)
            maxn.pop_back();
        maxn.push_back(i);
        if(!maxn.empty())
            tb = dr[maxn.front()].y;
        else
            tb = -1;
        // printf("maxn: ");
        // for(auto w:maxn){
        //     printf("%d ",w);
        // }
        // printf("\n");
        // printf("i:%d min:%d max:%d\n",i,ta,tb);

        if(tb-ta >= d) return 1;
    }
    //printf("\n");
    return 0;
}

void solve(){
    int l = 0,r = 2333333;
    while(l!=r){
        int mid = (l+r)>>1;
        if(judge(mid)) r = mid;
        else l = mid+1;
    }
    if(r == 2333333)
        printf("%d\n",-1);
    else
        printf("%d\n",l);
}

int main(){
    init();
    solve();
    return 0;
}