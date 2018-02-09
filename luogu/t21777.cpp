#include <cstdio>
#include <algorithm>
#define MAXN 500000
#define ll long long
#define lson (nown<<1)
#define rson (nown<<1|1)
using namespace std;

ll sumn[MAXN<<2],minn[MAXN<<2],maxn[MAXN<<2];

inline void push_up(int nown){
    sumn[nown] = sumn[lson]+sumn[rson];
    minn[nown] = min(minn[lson],minn[rson]);
    maxn[nown] = max(maxn[lson],maxn[rson]);
}

ll ge(int nown,int l,int r,int ql,int qr,ll val){
    if(maxn[nown]<=val)
        return 0;
    if(ql<=l&&r<=qr){
        if(minn[nown]>=val){
            ll ret = sumn[nown];
            sumn[nown] = val*(r-l+1);
            minn[nown] = maxn[nown] = val;
            return ret - sumn[nown];
        }
        if(maxn[nown])
    }
}

int main(){
    return 0;
}