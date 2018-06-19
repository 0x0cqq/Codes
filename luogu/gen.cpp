#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;

const ll MAXN = 10000000000;

int main(){
    srand(time(NULL));
    ll l = (rand()*111223137LL)%MAXN+MAXN,r = (rand()*1255353127LL)%MAXN+MAXN;
    if(l>r) swap(l,r);
    printf("%lld %lld\n",l,r);
    return 0;
}