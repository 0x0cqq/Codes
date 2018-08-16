#include <cstdio>
#include <algorithm>
using namespace std;


pair<int,char> num[10];

int w = 0;
char ans[100][100];

int n = 40,m = 39;

int main(){
    scanf("%d %d %d %d",&num[1].first,&num[2].first,&num[3].first,&num[4].first);
    num[1].second = 'a',num[2].second = 'b',num[3].second = 'c',num[4].second = 'd';
    sort(num+1,num+5);
    // for(int i = 1;i<=4;i++){
    //     printf("%d:%c\n",num[i].first,num[i].second);
    // }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(i == 1 || i == n || j == 1 || j == m || j%2 == 1){
                ans[i][j] = num[1].second;
            }
            else{
                ans[i][j] = '0';
            }
        }
    }
    num[1].first--;
    if(num[1].first != 0){
        while(num[1].first != 0){
            m++;
            for(int i = 1;i<=n;i++)
                ans[i][m] = num[2].second;
            m++;
            for(int i = 1;i<=n;i++){
                if(num[1].first == 0||(i%2) ^ (m&1))
                    ans[i][m] = num[2].second;
                else{
                    ans[i][m] = num[1].second,num[1].first--;
                }
            }
        }
        num[2].first --;
    }
    int nown = num[2].first == 0?3:2;
    for(int j = 1;j<=m;j++){
        for(int i = 1;i<=n;i++){
            if(ans[i][j] == '0'){
                if(nown > 4)
                    ans[i][j] = num[1].second;
                else if(ans[i-1][j] == num[nown].second)
                    ans[i][j] = num[1].second;
                else
                    ans[i][j] = num[nown].second,num[nown].first--;
                if(num[nown].first == 0)
                    nown++;
            }
        }
    }
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%s\n",ans[i] + 1);
    }
    return 0;
}