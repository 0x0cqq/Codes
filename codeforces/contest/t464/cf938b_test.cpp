#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n, prize[100005], result = 987654321;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &prize[i]);
    }
    result = min(result, prize[n - 1] - 1);
    result = min(result, 1000000 - prize[0]);
    for(int i = 0 ; i < n; i++)
    {
        result = min(result , max(prize[i] - 1, 1000000 - prize[i + 1]));
    }
    printf("%d", result);
}