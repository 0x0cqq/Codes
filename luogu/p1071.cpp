#include <cstdio>
#include <cstring>
using namespace std;

char a[256],b[256],x[256],r[26];

int main(){
    bool f = 0;
    scanf("%s %s %s",a,b,x);
    for (int i = 0; i < strlen(a); i++){
        if (r[a[i]-65]!=0 && r[a[i]-65]!=b[i]){
            f = 1;
            break;
        }
        else
            r[a[i]-65] = b[i];
    }
    for (int i = 0; i < 26; ++i){
        if(r[i] == 0)
            f = 1;
        for (int k = 0; k < 26; ++k)
            if (r[i] == r[k]&&i!=k){
                f = 1;
                break;
            }
    }
    if(f)
        printf("Failed\n");
    else{
        for (int i = 0; i < strlen(x); ++i)
            printf("%c", r[x[i]-65]);
        putchar('\n');
    }
    return 0;
}