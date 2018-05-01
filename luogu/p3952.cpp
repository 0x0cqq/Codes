#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct item{
    char c;
    int v;
    bool f;
};

int judge(int n,int aim){
    //1代表正确 0代表错误 -1代表语法问题
    //printf("%d %d\n",n,aim);
    stack<item> s;
    char ss[1000][100];bool vis[1000];
    char op[100],a[100],b[100],c[100];
    memset(vis,0,sizeof(vis));
    scanf("%[\n]",op);
    for(int i = 1;i<=n;i++){
        scanf("%[^\n]",ss[i]);
        getchar();
    }
    s.push((item){'!',0,true});
    for(int i = 1;i<=n;i++){
        char t[100];
        sscanf(ss[i],"%[^\n]",t);
        if(t[0] == 'F') sscanf(t,"%s %s %s %s",op,a,b,c);
        else sscanf(t,"%s",op);
        if(op[0] == 'F'){
            if(vis[a[0]]){
                return -1;
            }
            vis[a[0]] = 1;
            item now;now.c = a[0];now.f = 0;
            if(b[0] == 'n' && c[0] == 'n')
                now.v = 0;
            else if(b[0] != 'n' && c[0] == 'n')
                now.v = 1;
            else if(b[0] == 'n' && c[0] != 'n')
                now.v = -1;//!!!
            else if(b[0] != 'n' && c[0] != 'n')
                now.v = atoi(b) <= atoi(c)?0:-1;
            s.push(now);
            //printf("%dF: %c %d %d\n",i,now.c,now.v,int(now.f));
        }
        else if(op[0] == 'E'){
            if(s.empty()) return -1;
            item tmp = s.top();s.pop();
            //printf("%dE: %c %d %d\n",i,tmp.c,tmp.v,int(tmp.f));
            if(tmp.f == 0){
                if(s.empty()) return -1;
                if(s.top().f == 1)
                    s.top().v = max(s.top().v,tmp.v),vis[tmp.c] = 0;
                else if(s.top().f == 0)
                    tmp.f = 1,s.push(tmp),vis[tmp.c] = 0;
            }
            else if(tmp.f == 1){
                if(s.empty()) return -1;
                if(s.top().f == 0){
                    if(s.top().v == -1)
                        s.top().v = 0;
                    else
                        s.top().v += tmp.v == -1?0:tmp.v;
                    if(s.empty()) return -1;
                    tmp = s.top(),s.pop();
                    if(s.top().f == 1)
                        s.top().v = max(s.top().v,tmp.v),vis[tmp.c] = 0;
                    else if(s.top().f == 0)
                        tmp.f = 1,s.push(tmp),vis[tmp.c] = 0;
                }
                else{
                    return -1;
                }
            }
            //printf("%dEE: %c %d %d\n",i,s.top().c,s.top().v,int(s.top().f));
        }
    }
    if(s.top().f == 0 || s.size()!=1){
        return -1;
    }
    else{
        return s.top().v == aim?1:0;   
    }
}


int main(){
    int t;
    scanf("%d",&t);
    for(int i = 1;i<=t;i++){
        int n;char op[100];
        scanf("%d %s",&n,op);
        int f;
        if(op[2] != 'n'){
            f = judge(n,0);
        }
        else{
            int tmp;sscanf(op+4,"%d",&tmp);
            f = judge(n,tmp);
        }
        if(f == 0)
            printf("No\n");
        else if(f == 1)
            printf("Yes\n");
        else if(f == -1)
            printf("ERR\n");
    }
    return 0;
}