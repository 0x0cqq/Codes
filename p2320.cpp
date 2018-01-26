#include <cstdio>
#include <vector>
using namespace std;

int s = 1,n,ans = 0;

bool is_2x(int n){
    int k = 1;
    while(k<n){
        k<<=1;
    }
    return k == n;
}

vector<int> a;

int main(){
    scanf("%d",&n);
    a.push_back(1);
    while((s<<=1)-1<=n){
        a.push_back(s);
        ans++;
    }
    a.pop_back();
    s>>=1;
    n-=(s-1);
    if(n!=0){
        a.push_back(n);
        ans++;
    }
    printf("%d\n",ans);
    sort(a.begin(),a.end());
    for(int i = 0;i<a.size()-1;i++){
        if(a[i] == a[i+1]&&a[i]!=1){
            a[i]--;a[i+1]++;
        }
        printf("%d ",a[i]);
    }
    printf("%d\n",a.back());
    return 0;
}