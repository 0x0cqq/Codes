#include <cstdio>
using namespace std;

const int MAXN = 110;

namespace normal_io{
    void read(int &x){
        scanf("%d",&x);
    }
    char read(){
        return getchar();
    }
    void print(int x){
        printf("%d",x);
    }
    void print(char c){
        putchar(c);
    }
    void flush(){
        return;
    }
    void print(char *a){
        printf("%s",a);
    }
}using namespace normal_io;

char fff[10] = "false\n",ttt[10] = "true\n";

int n,m;
int qa[MAXN<<4],qb[MAXN<<4],qc[MAXN<<4];
int f[MAXN],r[MAXN];

int find(int x){
    if(f[x] == x) return x;
    int w = find(f[x]);
    r[x]+=r[f[x]];
    f[x] = w;
    return w;
}

bool un(int x,int y,int c){
    int x1 = find(x),y1 = find(y);
    if(x1!=y1){
        r[x1] = c - r[x] + r[y];
        f[x1] = y1;
        return true;
    }
    else{
        return r[x] - r[y] == c;
    }
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n+1;i++)
        f[i] = i,r[i] = 0;
    for(int i = 1;i<=m;i++)
        read(qa[i]),read(qb[i]),read(qc[i]);
}

void judge(){
    for(int i = 1;i<=m;i++){
        if(!un(qa[i],qb[i]+1,qc[i])){
            print(fff);
            return;
        }
    }
    print(ttt);
}

int main(){
    int T;
    read(T);
    for(int i = 1;i<=T;i++){
        init();
        judge();
    }
    return 0;
}