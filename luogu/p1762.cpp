#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 5100;

vector<int> edge[MAXN];

vector<int> ans;

int dfn[MAXN],low[MAXN],instack[MAXN],n,m,num = 1;

stack<int> p;

void dfs(int nown){
    /*for(int i = 0;i<num;i++){
        putchar(' ');
    }*/
    //printf("nown:%d num:%d\n",nown,num);
    dfn[nown] = low[nown] = num++;
    p.push(nown);instack[nown] = 1;
    for(int i:edge[nown]){
        if(dfn[i] == 0){
            dfs(i);
            low[nown] = min(low[i],low[nown]);
        }
        else if(instack[i]){
            low[nown] = min(low[nown],dfn[i]);
        }
    }
    if(dfn[nown] == low[nown]){
        int last = -1;
        vector<int> tmp;
        do{
            last = p.top();
            instack[last] = 0;
            tmp.push_back(last);
            p.pop();
        }while(last != nown);
        sort(tmp.begin(),tmp.end());
        if(tmp.size() > ans.size()){
            ans = tmp;
        }
        else if(tmp.size() == ans.size()){
            if(tmp < ans){
                ans = tmp;
            }
        }
    }
    /*for(int i = 0;i<num;i++){
        putchar(' ');
    }*/
    //printf("end! nown:%d dfn:%d lown: %d\n",nown,dfn[nown],low[nown]);
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=m;i++){
        int a,b,t;
        scanf("%d %d %d",&a,&b,&t);
        edge[a].push_back(b);
        if(t == 2){
            edge[b].push_back(a);
        }
    }
    for(int i = 1;i<=n;i++){
        if(dfn[i] == 0){
            dfs(i);
        }
    }
    int s = ans.size();
    printf("%d\n",s);
    for(int i = 0;i<s;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}