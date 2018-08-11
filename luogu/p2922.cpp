#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500000;

struct Trie{
    int c[MAXN][2],siz[MAXN],end[MAXN];
    int root,cnt;
    Trie(){root = cnt = 1;}
    void insert(int n,int *str){
        int nown = root;
        for(int i = 0;i<n;i++){
            siz[nown]++;
            if(!c[nown][str[i]])
                c[nown][str[i]] = ++cnt;
            nown = c[nown][str[i]];
        }
        siz[nown]++,end[nown]++;
    }
    int query(int n,int *str){
        int nown = root,ans = 0;
        for(int i = 0;i<n;i++){
            ans += end[nown];
            if(!c[nown][str[i]])
                return ans;
            nown = c[nown][str[i]];
        }
        ans += siz[nown];
        return ans;
    }
}T;

int m,n,t;
int s[MAXN];


int main(){
    scanf("%d %d",&m,&n);
    for(int i = 1;i<=m;i++){
        scanf("%d",&t);
        for(int i = 0;i<t;i++)
            scanf("%d",&s[i]);
        T.insert(t,s);
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&t);
        for(int i = 0;i<t;i++)
            scanf("%d",&s[i]);
        printf("%d\n",T.query(t,s));
    }
    return 0;
}