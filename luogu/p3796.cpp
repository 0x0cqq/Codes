#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200;

const int MAXC = 26,base_c = 'a';

struct answer{
    int id,v;
    bool operator < (answer a){
        return v > a.v;
    }
}ans[MAXN];

struct AC_automaton{
    struct node{
        int ch[MAXC];
        int end;
        int f,nex;
    }t[MAXN*70];
    struct q{
        int num[MAXN*70],b,e;
        q(){b = e = 0;}
        void pop(){b++;}
        void push(int x){num[e++] = x;}
        int front(){return num[b];}
        bool empty(){return b==e;}
        void clear(){b = e = 0;}
    }q;
    int cnt,root;
    void apply(int nown){
        if(t[nown].end) ans[t[nown].end].v++;
        if(t[nown].nex!=root) apply(t[nown].nex);
    }
    AC_automaton(){
        cnt = root = 1;
    }
    void clear(){
        cnt = root = 1;memset(t,0,sizeof(t));
    }
    void insert(char *str,int id){
        int nown = root;
        for(char *p = str;*p;p++)
            if(t[nown].ch[*p-base_c])
                nown = t[nown].ch[*p-base_c];
            else
                nown = t[nown].ch[*p-base_c] = ++cnt;
        if(t[nown].end == 0)t[nown].end = id;
    }
    void build(){
        q.clear();q.push(root);
        t[root].f = root,t[root].nex = root;
        /*
        for(int i = 0;i<MAXC;i++){
            int to = t[root].ch[i];
            if(to == 0)
                t[root].ch[i] = root,t[to].f = root;
        }
        */
        while(!q.empty()){
            int nown = q.front(),last = t[nown].f;q.pop();
            for(int i = 0;i<MAXC;i++){
                int &to = t[nown].ch[i];
                if(to!=0){
                    if(nown == root){
                        t[to].f = root;
                    }
                    else{
                        t[to].f = t[last].ch[i];
                    }
                    t[to].nex = t[t[to].f].end?t[to].f:t[t[to].f].nex;
                    //printf("to:%d %d\n",to,t[to].nex);
                    q.push(to);
                }
                else{
                    if(nown == root)
                        to = root;
                    else
                        to = t[t[nown].f].ch[i];
                }
            }
        }
    }
    void query(char *str){
        int nown = root;
        for(char *p = str;*p;p++){
            //printf("%d %c\n",nown,*p);
            nown = t[nown].ch[*p-base_c];
            apply(nown);
        }
    }
}ac;

int n;

char ch[200][70];

char a[1100000];

int main(){
    while(true){
        scanf("%d",&n);
        if(n == 0) return 0;
        ac.clear();
        memset(ans,0,sizeof(ans));
        for(int i = 1;i<=n;i++){
            scanf("%s",ch[i]);
            ac.insert(ch[i],i);
            ans[i].id = i;
        }
        ac.build();
        scanf("%s",a);
        ac.query(a);
        sort(ans+1,ans+n+1);
        printf("%d\n",ans[1].v);
        for(int i = 1;ans[1].v==ans[i].v;i++){
            printf("%s\n",ch[ans[i].id]);
        }
    }
    return 0;
}