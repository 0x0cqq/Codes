#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN = 300000;

struct Treap{
    int val[MAXN],son[MAXN][2],id[MAXN],p[MAXN];
    int cnt;
    Treap(){
        cnt = 1;
        srand(123123);
    }
    int newnode(int v,int i){
        int x = cnt++;
        val[x] = v,id[x] = i;
        son[x][0] = son[x][1] = 0;
    }
    int find(int v){
        int nown = 1;
        while(nown){
            if(v < val[nown]) nown = son[nown][0];
            else if(val[nown] < v) nown = son[nown][1];
            else break;
        }
        return nown;
    }
    void rotate(int &x,int t){
        //把t个儿子转上来
        int y = son[x][t];
        son[x][t] = son[y][1-t];
        son[y][1-t] = x;
        x = y;
    }
    void insert(int &x,int v,int i){
        if(x){
            int t = val[x] < x;
            insert(son[x][t],v,i);
            if(p[son[x][t]] < p[x])
                rotate(x,t);
        }
        else{
            x = newnode(v,i);
            p[x] = rand();
        }
    }
    void erase(int &x,int v){
        if(val[x] == x){
            if(son[x][0] == 0 && son[x][1] == 0){
                x = 0;return;
            }
            else{
                int t = p[son[x][0]] > p[son[x][1]];
                rotate(x,t);
                erase(x,v);
            }
        }
        else{
            erase(son[x][val[x] < v],v);
        }
    }
}idtree;


struct Splay{
    int val[MAXN],son[MAXN][2];
    int rg[MAXN][2],siz[MAXN];
    int cnt,root;
    void init(int n){
        root = cnt = 1;
        rg[root][0] = 1,rg[root][1] = n;
        siz[root] = n;
    }
    int newnode(int v,int l,int r){

    }
    
}ranktree;

int main(){
    return 0;
}