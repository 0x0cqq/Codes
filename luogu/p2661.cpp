#include <cstdio>
#include <cstring>
#include <algorithm>
#pragma gcc optimize(2)
using namespace std;

int road[210000],to[210000];
bool v[210000];
bool huan[210000];

inline int qr(){
    int f = 1,s = 0;char c = getchar();
    while(c<='0'||c>'9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        s = (s<<3)+(s<<1)+c-'0';
        c = getchar();
    }
    return f*s;
}

int n,minn= 0x3f3f3f3f;;

int dfs(int start){
    int now = start,times = 0;
    do{
        if(v[now])
            return 0x3f3f3f3f;
        v[now] = 1;
        now = now[road];
        times++;
        if(times>=minn)
            return 0x3f3f3f3f;
    }while(now!=start);
    do{
        huan[now] = 1;
        now = now[road];
    }while(now!=start);
    return times;
}

int main(){
    freopen("1.in","r",stdin);
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        road[i] = qr();
        to[road[i]]++;
    }
    /*for(int i = 1;i<=n;i++){
        printf("%d:%d ",i,to[i]);
    }*/
    for(int i = 1;i<=n;i++){
        int now = i;
        while(to[now] == 0){
            to[now] = -1;
            now = road[now];
            to[now]--;
            road[i] = 0;
        }
    }
    for(int i = n;i>=1;i--){
        if(huan[i]==0&&road[i]!=0){
            minn = min(minn,dfs(i));
        }
    }
    printf("%d\n",minn);
    return 0;
}