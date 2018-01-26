#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int n,p,v[128],f;
int w[128],r[128][128];
stack< pair<int,int> > path;


int dfs(int nown){
    int ans = 1;
    if(v[nown] == 1)
        return 0;
    else{
        v[nown] = 1;
        for(int i = 'A';i<='z';i++)
            if(r[nown][i]){
                //printf(":%d,%d\n",nown,i);
                ans+=dfs(i);
            }
    }
    return ans;
}

void euler(int now){
    for(int i = 'A';i<='z';i++){
        if(r[now][i]){
            r[now][i]--;r[i][now]--;
            euler(i);
            path.push(make_pair(now,i));
        }
    }
}

void print(){
    while(!path.empty()){
        putchar(path.top().first);
        if(path.size() == 1)
            putchar(path.top().second);
        path.pop();
    }
    putchar('\n');
}

int main(){
    scanf("%d",&n);getchar();getchar();
    for(int i = 0;i<n;i++){
        int a = getchar(),b = getchar();
        w[a] = 1;w[b] = 1;
        r[a][b]++;r[b][a]++;
        getchar();getchar();
    }
    for(int i = 'A';i<='z';i++){
        if(p == 0&&w[i])
            f = i;
        /*if(w[i])
            printf(":%d\n",i);
        */
        p+=w[i];
    }
    int t;
    if((t = dfs(f)) != p){
        printf("No Solution\n");
        return 0;
    }
    pair<int,int> a = make_pair<int,int>(0,0);
    for(int i = 'A';i<='z';i++){
        if(w[i] == 0)
            continue;
        int ans = 0;
        for(int j = 'A';j<='z';j++)
            ans+=r[i][j];
        if(ans&1){
            if(a.first == 0)
                a.first = i;
            else if(a.second == 0)
                a.second = i;
            else{
                printf("No Solution\n");
                return 0;
            }            
        }
    }
    if(a.first !=0&&a.second == 0){
        printf("No Solution\n");
        return 0;
    }
    else if(a.first != 0){
        euler(a.first);
        print();
    }
    else{
        euler(f);
        print();
    }
    return 0;
}