#include <cstdio>
#include <algorithm>
using namespace std;

int n,s,a,b;

struct apple{
    int h,l;
    bool operator <(const apple a)const{
        return l<a.l;
    }
}q[10000];

int main(){
    scanf("%d %d %d %d",&n,&s,&a,&b);
    a+=b;
    for(int i = 0;i<n;i++){
        scanf("%d %d",&(q[i].h),&(q[i].l));
    }
    b = 0;
    sort(q,q+n);
    for(int i = 0;i<n;i++){
        if(s-q[i].l<0)
            break;
        if(q[i].h<=a){
            b++;
            s -= q[i].l;
        }
    }
    printf("%d\n",b);
    return 0;
}