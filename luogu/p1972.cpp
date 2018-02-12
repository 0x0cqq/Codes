// luogu-judger-enable-o2
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Query{
    int id,l,r;
}query[201000];

int times[1001000];
int num[51000],n,m,q,res[201000];

bool cmp(Query a,Query b){
    if(a.l/q!=b.l/q){
        return a.l/q<b.l/q;
    }
    else{
        return (a.r < b.r) != ((a.l/q)&1);
    }
}



int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    scanf("%d",&m);
    for(int i = 0;i<m;i++){
        scanf("%d %d",&query[i].l,&query[i].r);
        query[i].id = i;
    }
    q = n/sqrt(m*2/3);
    sort(query,query+m,cmp);
    int l = 1,r = 1;
    int ans = 1;times[num[1]]++;
    for(int i = 0;i<m;i++){
        int ql = query[i].l,qr = query[i].r;
        while(ql<l){
            l--;if(times[num[l]]++ == 0) ans++;
        }
        while(r<qr){
            r++;if(times[num[r]]++ == 0) ans++;
        }
        while(l<ql){
            if(--times[num[l]] == 0) ans--;l++;
        }
        while(qr<r){
            if(--times[num[r]] == 0) ans--;r--;
        }
        res[query[i].id] = ans;
    }
    for(int i = 0;i<m;i++){
        printf("%d\n",res[i]);
    }
    return 0;
}