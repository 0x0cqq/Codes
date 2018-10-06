#include <bits/stdc++.h>

typedef long long LL;

using namespace std;

int N;
int x[100010],y[100010];

double calc(double X)
{
    double ret = 0;
    for (int i=1;i<=N;i++)
    {
        double dx = abs(X - x[i]);
        double R = (dx*dx+1.0*y[i]*y[i])/(2*y[i]);
        ret = max(ret,R);
    }
    return ret;
}

int main()
{
    scanf("%d",&N);
    int flag = 0;
    for (int i=1;i<=N;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        if (y[i] > 0) flag |= 1;
        else
        {
            y[i] = -y[i];
            flag |= 2;
        }
    }
    if (flag == 3)
    {
        puts("-1");
        return 0;
    }
    double L = -1e8, R = 1e8;
    for (int i=1;i<=100;i++)
    {
        double X1 = L + (R - L) / 3, X2 = R - (R - L) / 3;
        if (calc(X1) < calc(X2))
            R = X2;
        else
            L = X1;
    }
    printf("%.10lf\n",calc(L));
}