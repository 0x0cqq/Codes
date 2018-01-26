#include <cstdio>
#include <algorithm>
using namespace std;

struct student{
    int id,a,b,c,sum;
    bool operator <(const student d)const{
        if(sum<d.sum) return false;
        else if(sum>d.sum) return true;
        else{
            if(a<d.a) return false;
            else if(a>d.a) return true;
            else{
                if(id>d.id) return false;
                else return true;
            }
        }
    }
    void cal(){
        sum = a+b+c;
    }
}s[305];

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d %d %d",&(s[i].a),&(s[i].b),&(s[i].c));
        s[i].id = i;
        s[i].cal();
    }
    sort(s+1,s+n+1);
    for(int i = 1;i<=5;i++){
        printf("%d %d\n",s[i].id,s[i].sum);
    }
    return 0;
}