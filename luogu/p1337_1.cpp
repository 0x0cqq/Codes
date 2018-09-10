#include <iostream>
#include <cmath>
#include <cstdio>
#define abs(x) ((x) >= 0 ? (x) : (-(x)))
using namespace std;
int n;
double x, y;
bool XF = true, YF = true;//原点移动的方向 true 代表正方向，false 代表负方向
struct Position {
    int x;
    int y;
    int power;
} positions[1005];
void solve(double move) {
    double X, Y, temp;
    X = Y = 0;
    for (int i = 1; i <= n; i++) {
        temp = sqrt((x - positions[i].x) * (x - positions[i].x) + (y - positions[i].y) * (y - positions[i].y));//记录该点到原点的欧几里得距离
        if (temp == 0)//判断是否与原点重合
            continue;
        //若不重合则进行正交分解
        X += positions[i].power / temp * (positions[i].x - x);
        Y += positions[i].power / temp * (positions[i].y - y);
    }
    temp = sqrt(X * X + Y * Y);//计算正交分解后的合力
    //将原点在合力方向上位移一定距离
    x += move / temp * X;
    y += move / temp * Y;
}
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &positions[i].x, &positions[i].y, &positions[i].power);
    //move：移动的步长  tx ty 保存移动前的原点的位置
    double move = 5000, tx, ty;
    while (true) {
        //记录移动前原点的位置
        tx = x;
        ty = y;
        solve(move);//按照步长移动原点
        if (abs(tx - x) < 0.00001 && abs(ty - y) < 0.00001)//判断是否满足要求
            break;
        if ((XF != (x > tx)) || (YF != (y > ty))) {//如果移动方向发生改变
            //记录移动方向
            XF = !x > tx;
            YF = !y > ty;
            move = move * 0.9;//缩小移动方向
        }
    }
    printf("%.3f %.3f", x, y);
    return 0;
}