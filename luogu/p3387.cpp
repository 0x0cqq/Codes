#include <cstdio>
#include <cctype>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

namespace fast_io {
    inline char read() {
		//return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))== s)?-1:*s++) : *s++;
    }
    inline void read(int &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            	x = ((x+(x<<2))<<1) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c =='\n')){
            c = read();
        }
        while(c!= -1&&c!=' '&&c!='\n'){
            *a++ = c;
            c = read();
        }
        *a = 0;
    }*/
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x) {
        static int buf[30], cnt;
        if (x == 0) {
            print('0');
        }
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    /*
    inline void print(char *a){
        while(*a) print(*a++);
    }
    */
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

namespace normal_io{
    inline char read(){
        return getchar();
    }
    inline void read(int &x){
        scanf("%d",&x);
    }
    inline void print(int x){
        printf("%d",x);
    }
    inline void print(char x){
        putchar(x);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

const int MAXN = 11000;

int n,m,cnt = 1,colnum = 0;
int maxx[MAXN];
int num1[MAXN],dfn[MAXN],low[MAXN],col[MAXN],num2[MAXN],instack[MAXN];
vector<int> edge1[MAXN],edge2[MAXN];

stack<int> ss;

void addedge(int a,int b,int w){
    if(w == 1)
        edge1[a].push_back(b);
    else if(w == 2)
        edge2[a].push_back(b);
    else
        printf("!!!!\n");
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(num1[i]);
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(a,b,1);
    }
}

void dfs(int nown){
    dfn[nown] = low[nown] = cnt++;
    ss.push(nown),instack[nown] = 1;
    for(int i = 0;i<edge1[nown].size();i++){
        int to = edge1[nown][i];
        if(dfn[to] == 0)
            dfs(to),low[nown] = min(low[nown],low[to]);
        else if(instack[to] == 1)
            low[nown] = min(low[nown],dfn[to]);
    }
    if(dfn[nown] == low[nown]){
        int j = -1,sumn = 0;
        colnum++;
        do{
            j = ss.top();ss.pop();
            instack[j] = 0; 
            sumn+=num1[j],col[j] = colnum;
        }while(j!=nown);
        num2[colnum] = sumn;
    }
}

inline void tarjan(){
    for(int i = 1;i<=n;i++)
        if(dfn[i] == 0)
            dfs(i);
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<edge1[i].size();j++){
            int to = edge1[i][j];
            if(col[i]!=col[to])
                addedge(col[i],col[to],2);
        }
    }
}

int dfs2(int nown){
    if(maxx[nown]!= 0x3f3f3f3f) 
        return maxx[nown];
    int tmp = 0;
    for(int i = 0;i<edge2[nown].size();i++){
        int to = edge2[nown][i];
        tmp = max(tmp,dfs2(to));
    }
    return maxx[nown] = tmp + num2[nown];
}

void __print(){
    for(int i = 1;i<=colnum;i++){
        printf("i:%d num:%d\n",i,num2[i]);
        for(int j = 0;j<edge2[i].size();j++){
            int to = edge2[i][j];
            printf("%d\n",to);
        }
    }
}

void solve(){
    memset(maxx,0x3f,sizeof(maxx));
    int ans = -0x3f3f3f3f;
    for(int i = 1;i<=colnum;i++){
        if(maxx[i] == 0x3f3f3f3f)
            dfs2(i);
        ans = max(ans,maxx[i]);
    }
    print(ans),print('\n');
}


int main(){
    init();
    tarjan();
    //__print();
    solve();
    flush();
    return 0;
}