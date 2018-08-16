#include <cstdio>
using namespace std;

const int MAXN = 110000;

int n,m,q;
char a[MAXN],b[MAXN];

int sumn[MAXN];

int getsum(int i){
    if(i < 0) return 0;
    else{
        return sumn[i];
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&q);
    scanf("%s",a);
    scanf("%s",b);
    for(int i = 0;i<n;i++){
        bool flag = 1;
        for(int j = 0;j<m;j++){
            if(i + m-1 >= n){
                flag = 0;
                break;
            }
            if(a[i+j] != b[j]){
                flag = 0;
                break;
            }
        }
        if(flag){
            sumn[i+1] = sumn[i] + 1;
        }
        else{
            sumn[i+1] = sumn[i];
        }
    }
    // for(int i = 1;i<=n;i++){
    //     printf("%d ",sumn[i]);
    // }
    for(int i = 1;i<=q;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(r-l+1 < m)
            printf("%d\n",0);
        else
            printf("%d\n",getsum(r-m+1)-getsum(l-1));
    }
    return 0;
}