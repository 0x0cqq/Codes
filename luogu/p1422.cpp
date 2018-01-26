#include <cstdio>
using namespace std;

int main(){
    int a;double res = 0;
    scanf("%d",&a);
    if(a<=150)
        res = 0.4463*a;
    else if(a<=400)
        res = 0.4463*150+0.4663*(a-150);
    else
        res = 0.4463*150+0.4663*250+0.5663*(a-400);
    printf("%.1lf\n",res);
    return 0;
}