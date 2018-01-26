#include <cstdio>
using namespace std;

inline bool p(int *k_1,int *water_1,int n_1,int m_1){
    for(int i = 0;i<n_1;i++)
        if(k_1[i]!=0||water_1[i]!=0) return false;
    return true;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int k[n],water[m];
    for(int i = 0;i<n;i++){
        scanf("%d",k+i);
        if(i<m){
            water[i] = k[i];
            k[i] = 0;
        }
    }
    int now = m;
    for(int time = 0;;time++){
        if(p(k,water,n,m)){
            printf("%d\n",time);
            return 0;
        }
        for(int i = 0; i<m ;++i){
            if(water[i]) 
                --water[i];
            if(water[i] == 0 && now < n){
                water[i] = k[now];
                k[now]=0;
                ++now;
            }
        }
    }
    return 0;
}