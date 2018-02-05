#include <cstdio>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

struct question{
    int id,l,r;
}query[60000];

int times[60000],num[60000],n,m,k,q;

ll res[60000];

bool cmp(question a,question b){
    if(a.l/q!=b.l/q)
        return a.l/q<b.l/q;
    else
        return a.r<b.r;
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    q = sqrt(n);
    for(int i = 1;i<=n;i++)
        scanf("%d\n",&num[i]);
    for(int i = 0;i<m;i++){
        scanf("%d %d",&query[i].l,&query[i].r);
        query[i].id = i;
    }
    sort(query,query+m,cmp);
    int l = 1,r = 1;
    ll ans = 1;
    times[num[1]]++;
    for(int i = 0;i<m;i++){
        int ql = query[i].l,qr = query[i].r;
        while(ql<l){
            l--;
            ans += times[num[l]]*2+1;
            times[num[l]]++;
        }
        while(r<qr){
            r++;
            ans += times[num[r]]*2+1;
            times[num[r]]++;
        }
        while(l<ql){
            times[num[l]]--;
            ans -= times[num[l]]*2+1;
            l++;            
        }
        while(qr<r){
            times[num[r]]--;
            ans -= times[num[r]]*2+1;
            r--;            
        }
        res[query[i].id] = ans;
    }
    for(int i = 0;i<m;i++){
        printf("%lld\n",res[i]);
    }
    return 0;
}