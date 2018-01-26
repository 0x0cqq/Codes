#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int s,p,dis[600][600],point[600][2],color[600];
vector<int> d;
set<int> d_s;

void dfs(int nown,int c,int nowd){
    color[nown] = c;
    for(int i = 0;i<p;i++){
        if(color[i]==0 && dis[nown][i]<=nowd){
            dfs(i,c,nowd);
        }
    }
}

int colored(int nowd){
    memset(color,0,sizeof(color));
    int nowc = 0;
    for(int i = 0;i<p;i++){
        if(color[i]!=0)
            continue;
        else{
            nowc++;
            dfs(i,nowc,nowd);
        }
    }
    return nowc;
}

int main(){
    scanf("%d %d",&s,&p);
    if(s == 0)
        s = 1;
    for(int i = 0;i<p;i++){
        scanf("%d %d",&point[i][0],&point[i][1]);
        for(int j = 0;j<i;j++){
            dis[i][j] = dis[j][i] = (point[i][0]-point[j][0])*(point[i][0]-point[j][0])+(point[i][1]-point[j][1])*(point[i][1]-point[j][1]);
            if(d_s.count(dis[i][j]) == 0){
                d_s.insert(dis[i][j]);
                d.push_back(dis[i][j]);
            }
        }
    }
    sort(d.begin(),d.end());
    //printf("!!!!!!\n\n");
    int b = 0,e = d.size()-1;
    while(b!=e){
        //printf("%d %d\n",b,e);
        int mid = (b+e)/2;
        if(colored(d[mid])>s){
            b = mid+1;
        }
        else{
            e = mid;
        }
    }
    printf("%.2lf\n",sqrt(d[b]));
    return 0;
}