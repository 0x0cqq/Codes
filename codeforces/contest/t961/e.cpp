#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 310000;

int n;
int num[MAXN];

int lowbit(int x){
    return x&(-x);
}

int tree[MAXN<<2];

int query(int w){
    int ans = 0;
    for(int nown = w;nown<=n;nown += lowbit(nown)){
        ans+=tree[nown];
    }
    return ans;
}

void add(int pos,int val){
    for(int nown = pos;nown >= 1;nown -= lowbit(nown)){
        tree[nown]+=val;
    }
}

vector<pair<int,int> > a;

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
        if(num[i]>n) num[i] = n;
        a.push_back(make_pair(num[i],i));
    }
    long long ans = 0;
    sort(a.begin(),a.end());
    int nown = 0;
    for(int i = 0;i<n;i++){
        //printf("%d %d %d\n",nown,a[i].first,a[i].second);
        while(nown<a[i].first){
            nown++;
            add(num[nown],1);
        }
        add(a[i].first,-1);
        ans+=query(a[i].second);
        add(a[i].first,1);
    }
    printf("%lld\n",ans/2);
    return 0;
}