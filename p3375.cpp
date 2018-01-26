#include <cstdio>
#include <cstring>
using namespace std;

char s1[10000000],s2[11000000];
int next[11000000];

int l_1,l_2,cnt;

void prepare(){
    next[0] = 0;
    l_2 = strlen(s2);
    int j = 0;
    for(int i = 1;i<l_2;i++){
        while(j>0 && s2[i]!=s2[j])
            j = next[j-1];
        if(s2[i]==s2[j]) ++j;
        next[i] = j;
    }
}

void compare(){
    cnt = 0;l_1 = strlen(s1);
    int j = 0;
    for(int i = 0;i<l_1;i++){
        while(j && s1[i]!=s2[j])
            j = next[j-1];
        if(s1[i] == s2[j]) ++j;
        if(j == l_2)
            printf("%d\n",i-l_2+2);
    }
}


int main(){
    scanf("%s%s",s1,s2);
    prepare();
    //printf("!!!!!\n");
    compare();
    //printf("%s\n%s\n",s1,s2);
    for(int i = 0;i<l_2;i++)
        printf("%d ",next[i]);
    putchar('\n');
    return 0;
}