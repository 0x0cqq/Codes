#include <cstdio>
#include <algorithm>
using namespace std;


#define pp pair<int,int>
int n;

const int MAXN = 210000;

pp q[MAXN];
int a[MAXN],b[MAXN];

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    int tmp = -1;
    for(int i = 1;i<=10;i++){
        int start = rand()%n+1;
        for(int i = 1;i<=n;i++){
            if(b[i]>a[i]) swap(a[i],b[i]);
            q[i].first = a[i],q[i].second = b[i];
            if(q[i].second<start && q[i].first<start)
                q[i].first += 2*n,q[i].second+=2*n;
            else if(q[i].second<start && q[i].first >= start){
                q[i].second+=2*n;swap(q[i].first,q[i].second);
            }
        }
        sort(q+1,q+n+1);
        int ans = 0,t = 0;
        for(int i = 1;i<=n;i++){
            //printf("%d %d\n",q[i].first,q[i].second);
            if(q[i].second > t)
                ans++,t = q[i].first;
        }
        tmp = max(ans,tmp);
    }
    printf("%d\n",(tmp-1)/2+1);
    return 0;
}