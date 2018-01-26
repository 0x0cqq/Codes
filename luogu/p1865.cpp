#include <cstdio>
#include <cstring>
using namespace std;

bool p[1000010];
int su[1000010],ge[1000010];

void prime(int k){
    int cnt = 0;
    memset(p,1,k+1);
    p[1] = 0;
    for(int i = 2;i<=(k+1)/2;i++){
        if(p[i]){
        	su[cnt++] = i;
        }
        for(int j = 0;j<cnt&&su[j]*i<=k;j++){
            p[su[j]*i] = 0;
            if(i%su[j] == 0)
                break;
        }
    }
    ge[0] = 0;
    for(int i = 1;i<=k;i++){
        ge[i] = ge[i-1]+p[i];
    }
}


int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    prime(m);
    for(int i = 0;i<n;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(l<1||l>m||r<1||r>m){
            printf("Crossing the line\n");
        }
        else{
            printf(":%d\n",ge[r]-ge[l-1]);
        }
    }
    return 0;
}