#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

bool cmp_1(pii a,pii b){
    if(a.first!=b.first)
        return a.first<b.first;
    else{
        return a.second<b.second;
    }
}

vector<int> l;

int main(){
    vector<pii> w;
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int a,b;scanf("%d %d",&a,&b);
        pii now;
        now.first = a;now.second = b;
        w.push_back(now);
    }
    sort(w.begin(),w.end(),cmp_1);
    for(auto i = w.rbegin();i!=w.rend();i++){
        auto x = lower_bound(l.begin(),l.end(),i->second);
        if(x == l.end()){
            l.push_back(i->second);
        }
        else{
            *x = i->second;
        }
    }
    printf("%d\n",l.size());
    return 0;
}