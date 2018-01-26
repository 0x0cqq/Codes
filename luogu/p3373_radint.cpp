#include <cstdio>
#include <random>
#include <ctime>
using namespace std;

int main(){
    freopen("1.txt","w",stdout);
    srand(time(NULL));
    long long m = rand(),n = rand(),p = rand();
    printf("%lld %lld %lld\n",n,m,p);
    for(int i = 0;i<n;i++){
        int opt = rand()%3+1;
        printf("%d ",opt);
        if(opt == 1){
            
        }
    }
    
    return 0;
}