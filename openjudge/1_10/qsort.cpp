#include <cstdio>
#include <algorithm>
using namespace std;

struct Stu
{
    char name[20];
    int score;
    Stu *next;
};

int s[500],w[500];

int main(){
    int n,tot = 0;
    scanf("%d",&n);
    for (size_t i = 0; i < n; i++){
        scanf("%d",&(s[i]));
        if(s[i]&1){
            w[tot] = s[i];
            tot++;
        }
    }
    printf("%d",w[0]);
    for (size_t i = 1; i < tot; i++){
        printf(",%d",w[i]);
    }
    return 0;
}