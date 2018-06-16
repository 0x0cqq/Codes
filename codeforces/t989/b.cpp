#include <cstdio>
using namespace std;

const int MAXN = 3000;

int n,p;
char s[MAXN];

int main(){
    scanf("%d %d",&n,&p);
    scanf("%s",s+1);
    bool flag = 1;
    for(int i = 1,j = p+1;j<=n;i++,j++){
        if(s[i] == '.' && s[j] == '.')
            flag = 0;
        else if(s[i] != '.' && s[j] != '.'){
            if(s[i]!=s[j])
                flag = 0;
        }
        else{
            if(s[i] =='.')
                s[i] = s[j]^1;
            else
                s[j] = s[i]^1;
            flag = 0;
        }
        //printf("%s\n",s+1);
    }
    for(int i = 1;i<=n;i++){
        if(s[i] =='.')
            s[i] = '0';
    }
    if(flag)
        printf("No\n");
    else
        printf("%s\n",s+1);
    return 0;
}