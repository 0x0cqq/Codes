#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n,w;
int ans = 0;

struct wupin{
    int va;
    int po;
}k[200];

int a[200],b[200];

bool cmp_1(wupin a,wupin b){
    return a.va<b.va;
}

int dd[10000100];

void beibao(int begin,int end){
    for(int i = begin;i<end;i++){
        for(int j = w;j>=k[i].va;j--){
            if(dd[j-k[i].va]+k[i].po>=dd[j])
                dd[j] = dd[j-k[i].va]+k[i].po; 
        }
    }
}

int main(){
    scanf("%d %d",&n,&w);
    for(int i = 0;i<n;i++){
        scanf("%d %d",&(k[i].va),&(k[i].po));
    }
    sort(k,k+n,cmp_1);
    for(int i = 0;i<n;i++){
        a[i] = k[i].va;
    }
    for(int l = 0;l<n;l++){
        if((l != 0) && k[l].va == k[l-1].va){
            continue;
        }
        int high = upper_bound(a,a+n,k[l].va+3)-a;
        memset(dd,0,sizeof(dd));
        beibao(l,high);
        ans = max(ans,dd[w]);
    }
    printf("%d\n",ans);
    return 0;
}