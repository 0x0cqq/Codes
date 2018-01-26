#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int base = 101,n;

pair<int,int> a[20000];

int _hash(string w,int mod){
    int ans = 0;
    for(int i = w.size()-1;i>=0;i--){
        ans*=base;ans+=w[i];ans%=mod;
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        string t;
        cin >> t;
        a[i] = make_pair(_hash(t,19260817),_hash(t,19260813));
        //printf("%d %d\n",_hash(t,19260817),_hash(t,19260813));
    }
    sort(a,a+n);
    int ans = 0;
    for(int i = 0;i<n;i++){
        if(i == 0) ans++;
        else if(a[i] != a[i-1]) ans++;
    }
    printf("%d\n",ans);
    return 0;
}