#include <cstdio>
#include <algorithm>
using namespace std;

struct student{
    char name[100];
    int id;
    int a,b,x;
    bool c,d;
    int j = 0;
    int cal(){
        if(a>80&&x>=1)
            j+=8000;
        if(a>85&&b>80)
            j+=4000;
        if(a>90)
            j+=2000;
        if(a>85&&d)
            j+=1000;
        if(b>80&&c)
            j+=850;
        return j;
    }
}s[1000];

bool cmp(student a,student b){
    if(a.j == b.j)
        return a.id < b.id;
    else
        return a.j>b.j;
}

int main(){
    int n,sum = 0;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        s[i].id = i;
        scanf("%s %d %d",s[i].name,&(s[i].a),&(s[i].b));
        getchar();
        if(getchar() == 'Y')
            s[i].c = 1;
        else
            s[i].c = 0;
        getchar();
        if(getchar() == 'Y')
            s[i].d = 1;
        else
            s[i].d = 0;
        getchar();
        scanf("%d",&(s[i].x));
        getchar();
        sum+=s[i].cal();
    }
    sort(s,s+n,cmp);
    printf("%s\n%d\n%d\n",s[0].name,s[0].j,sum);
    return 0;
}