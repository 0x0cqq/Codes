#include <cstdio>
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
using namespace std;

inline int qr(){
    int f = 1,s = 0;char c = getchar();
    while(c<'0'||c>'9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        s = (s<<3)+(s<<1)+c-48;
        c = getchar();
    }
    return f*s;
}

inline int count(int k){
    int ans;
    for(ans = 0;k;ans++)
        k&=(k-1);
    return ans;
}

int tree[500000],lazy[500000];

inline void maintain(int nown){
    tree[nown] = tree[lson] | tree[rson];
}

inline void build(int nown,int l,int r){
    tree[nown] = lazy[nown] = (1<<1);
}

inline void push_down(int nown){
    if(lazy[nown]){
        tree[lson] = tree[rson] = lazy[nown];
        lazy[lson] = lazy[rson] = lazy[nown];
        lazy[nown] = 0;
    }
}

inline void update(int nown,int l,int r,int ql,int qr,int color){
    if(ql<=l&&r<=qr)
        tree[nown] = lazy[nown] = (1<<color);
    else{
        push_down(nown);
        if(ql<=mid) update(lson,l,mid,ql,qr,color);  
        if(qr>=mid+1) update(rson,mid+1,r,ql,qr,color);  
        maintain(nown);
    }
} 

inline int query(int nown,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr)
        return tree[nown];
    else{
        push_down(nown);
        int res = 0;
        if(ql<=mid) res|= query(lson,l,mid,ql,qr);
        if(qr>=mid+1) res|= query(rson,mid+1,r,ql,qr);
        return res;
    }
}


int main(){
    int l,t,o;
    l = qr(); t = qr();o = qr();
    build(1,1,l);
    for(int i = 0;i<o;i++){
        char ch[20];int a,b,c;
        scanf("%s",ch);
        a = qr();b = qr();
        if(b<a) a^=b,b^=a,a^=b;
        switch(ch[0]){
            case 'C':c = qr();update(1,1,l,a,b,c);break;
            case 'P':printf("%d\n",count(query(1,1,l,a,b)));break;
        }
    }
    return 0;
}