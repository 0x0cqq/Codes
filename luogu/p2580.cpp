#include <cstdio>
#include <algorithm>
using namespace std;

struct Trie{
    static const int MAXN = 1000000,MAXC = 26;
    struct node{
        int nex[MAXC];
        bool exist,rep;
        node(){
            for(int i = 0;i<26;i++)
                nex[i] = 0;
            exist = 0,rep = 0;
        }
    }t[MAXN];
    int cnt,root = 1;
    Trie(){
        cnt = root = 1;
    }
    void insert(char *str){
        int nown = root;
        for(char *p = str;*p;p++){
            if(t[nown].nex[*p-'a'])
                nown = t[nown].nex[*p-'a'];
            else 
                nown = t[nown].nex[*p-'a'] = ++cnt;
        }
        t[nown].exist = 1;
    }
    int query(char *str){
        //return 0 -> wrong
        //return 1 -> right
        //return 2 -> repeat
        int nown = root;
        for(char *p = str;*p;p++){
            if(t[nown].nex[*p-'a'])
                nown = t[nown].nex[*p-'a'];
            else 
                return 0;
        }
        return t[nown].rep?2:t[nown].exist?t[nown].rep = 1:0;
    }
    void print(){
        for(int i = 1;i<=cnt;i++){
            printf("%d: %d %d\n",i,int(t[i].exist),int(t[i].rep));
            for(int j = 0;j<30;j++){
                if(t[i].nex[j])
                    printf("    %d:%d\n",j,t[i].nex[j]);
            }
        }
    }
}trie;

int n,m;


void init(){
    scanf("%d",&n);
    char ch[100];
    for(int i = 1;i<=n;i++){
        scanf("%s",ch);
        trie.insert(ch);
    }
    //trie.print();
}

void solve(){
    scanf("%d",&m);
    char ch[100];
    for(int i = 1;i<=m;i++){
        scanf("%s",ch);
        int w = trie.query(ch);
        if(w == 0){
            printf("WRONG\n");
        }
        else if(w == 1){
            printf("OK\n");
        }
        else if(w == 2){
            printf("REPEAT\n");
        }
        else{
            printf("!!!\n");
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}