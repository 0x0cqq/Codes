#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 51000;

int q1[MAXN],q2[MAXN];

int n,block;

inline void add(int pos,int val){
    q1[pos]+=val;
    q2[pos/block]+=val;
}

inline int query(int pos){
    int ans = 0;
    int dst = ((pos)/block)*block;
    while(pos>=dst){
        ans+=q1[pos];
        pos--;
    }
    dst/=block;
    dst--;
    while(dst>=0){
        ans+=q2[dst];
        dst--;
    }
    return ans;
}

void print(){
    printf("---------------\n");
    printf("block:%d\n",block);
    for(int i = 1;i<=n;i++){
        printf("%d:%d\n",i,q1[i]);
    }
    for(int i = 0;i<=n/block;i++){
        printf("%d:%d\n",i,q2[i]);
    }
    printf("---------------\n");
}

int main(){
    scanf("%d",&n);
    block = sqrt(n);
    int t,last = 0;
    for(int i = 1;i<=n;i++){
        scanf("%d",&t);
        add(i,t-last);
        last = t;
    }
    for(int i = 1;i<=n;i++){
        int opt,l,r,c;
        scanf("%d %d %d %d",&opt,&l,&r,&c);
        if(opt == 0){
            add(l,c);add(r+1,-c);
        }
        else{
            printf("%d\n",query(r));
        }
    }
    return 0;
}