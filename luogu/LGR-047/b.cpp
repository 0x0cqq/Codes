#include <cstdio>
#include <algorithm>
#include <random>
#define pp pair<double,double>
using namespace std;
default_random_engine e;

int l,n;

double dis;

pp p[20];

inline bool judge(double x,double y,int num){
    return (x-p[num].first)*(x-p[num].first)+(y-p[num].second)*(y-p[num].second) > dis*dis;
}

int main(){
    scanf("%d %d",&n,&l);
    dis = double(l)/n;
    for(int i = 1;i<=n;i++){
        scanf("%lf %lf",&p[i].first,&p[i].second);
    }
    uniform_real_distribution<double> u(0.0, double(l));
    for(int j = 1;j<=2000000;j++){
        double x = u(e),y = u(e);
        for(int i = 1;i<=n;i++){
            if(!judge(x,y,i)) break;
            if(i == n){
                printf("%lf %lf\n",x,y);
                return 0;
            }
        }
    }
    printf("GG\n");
    return 0;
}