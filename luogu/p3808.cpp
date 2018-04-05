#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int ans = 0;

struct AC_automaton{
    static const int MAXN = 1110000,MAXC = 26;
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
            if(end[nw]) ans+=end[nw],end[nw] = 0;
            int tmp = l[nw];
            l[nw] = 0;
            nw = tmp;
        }
    }
    void insert(char *str){
        int nw = root;
        for(char *p = str;*p;p++){
            if(!c[nw][*p-'a'])
                c[nw][*p-'a'] = ++cnt;
            nw = c[nw][*p-'a'];
        }
        end[nw]++;
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

char ch[2100000];

char a[2100000];

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%s",ch);
        ac.insert(ch);
    }
    ac.build();
    scanf("%s",a);
    ac.query(a);
    printf("%d\n",ans);
    return 0;
}