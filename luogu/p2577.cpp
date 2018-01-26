#include <cstdio>
#include <algorithm>
#define pp pair<int,int>
using namespace std;

pp person[500];int q[500];
int dd[210][41000];
int n,sumn = 0;

bool cmp(pp a,pp b){
    if(a.second!=b.second)
        return a.second>b.second;
    else
        return a.first<b.first;
}

int dp(int k,int i){
    if(dd[k][i])
        return dd[k][i];
    if(k == n+1)
        return max(i,q[k-1]-i);
    int res = 0x3f3f3f3f;
    int a = person[k].first;int b = person[k].second;
    res = min(max(dp(k+1,i+a),i+a+b),max(dp(k+1,i),q[k-1]-i+a+b));
    return dd[k][i] = res;
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&person[i].first,&person[i].second);
        sumn+=person[i].first;
    }
    sort(person+1,person+n+1,cmp);
    for(int i = 1;i<=n;i++)
        q[i] = person[i].first+q[i-1];
    printf("%d\n",dp(1,0));
    return 0;
}