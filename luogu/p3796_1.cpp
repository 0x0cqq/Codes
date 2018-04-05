#include <cstdio>
#include <queue>
#include <cctype>
#include <cstring>
using namespace std;

const int MAXN = 200;

int maxn,ans[MAXN];

struct AC_automaton{
    static const int MAXN = 210000,MAXC = 26;
    int f[MAXN],c[MAXN][MAXC],l[MAXN],end[MAXN];
    int root,cnt;
    AC_automaton(){
        root = cnt = 1;
    }
    void clear(){
        memset(f,0,sizeof(f));
        memset(c,0,sizeof(c));
        memset(l,0,sizeof(l));
        memset(end,0,sizeof(end));
        root = cnt = 1;
    }
    void apply(int u){
        int nw = u;
        while(nw){
            if(end[nw] && ++ans[end[nw]] > maxn) maxn = ans[end[nw]];
            nw = l[nw];
        }
    }
    void insert(char *str,int id){
        int nw = root;
        for(char *p = str;*p;p++){
            if(!c[nw][*p-'a'])
                c[nw][*p-'a'] = ++cnt;
            nw = c[nw][*p-'a'];
        }
        if(!end[nw])end[nw] = id;
    }
    void build(){
        queue<int> q;
        while(!q.empty()) q.pop();
        f[root] = root,l[root] = 0;
        for(int i = 0;i<MAXC;i++){
            if(!c[root][i]){
                c[root][i] = root;continue;
            }
            f[c[root][i]] = root,l[c[root][i]] = 0;
            q.push(c[root][i]);
        }
        while(!q.empty()){
            int nw = q.front();q.pop();
            //printf("%d: %d %d %d\n",nw,f[nw],l[nw],end[nw]);
            for(int i = 0;i<MAXC;i++){
                if(!c[nw][i]){
                    c[nw][i] = c[f[nw]][i];continue;
                }
                f[c[nw][i]]=c[f[nw]][i];
                l[c[nw][i]]=end[f[c[nw][i]]]?f[c[nw][i]]:l[f[c[nw][i]]];
                q.push(c[nw][i]);
            }
        }
    }
    void query(char *str){
        int nw = root;
        for(char *p = str;*p;p++){
            nw = c[nw][*p-'a'];
            apply(nw);
        }
    }
}ac;

int n;

char ch[MAXN][MAXN];
char T[1010000];

void init(){
    read(n);
    maxn = -1;
    memset(ans,0,sizeof(ans));
    ac.clear();
    for(int i = 1;i<=n;i++){
        read(ch[i]);
        ac.insert(ch[i],i);
    }
}

void solve(){
    ac.build();
    read(T);
    ac.query(T);
    print(maxn),print('\n');
    for(int i = 1;i<=n;i++)
        if(ans[i] == maxn)
            print(ch[i]),print('\n');
}

int main(){
    while(true){
        init();
        if(n == 0)
            break;
        solve();
    }
    flush();
    return 0;
}