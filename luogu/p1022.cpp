#include <cstdio>
#include <cstring>
using namespace std;


int main(){
    int lx = 0,lc = 0,rx = 0,rc = 0;
    char x = 0;
    char l[1000],r[1000];
    scanf("%[^=]",l);
    getchar();
    scanf("%[^\r\n]",r);
    //printf("%s\n%s\n",l,r);
    for(int i = 0;i<strlen(l);){
        if(i >= strlen(l))
            break;
        //printf("%d\n",l[1]);
        int s = 0,w = 1;
        while ((l[i] <= '0' || l[i] > '9')&&!((l[i]>='a')&&(l[i]<='z'))){
            if (l[i] == '-')
                w = -1;
            i++;
        }
        while (l[i] >= '0' && l[i] <= '9') {
            s = s * 10 + l[i] - '0' ;
            i++;
        }
        if(i > strlen(l))
            break;
        if(l[i]!='-'&&l[i]!='+'&&l[i]!='\0'&&l[i]!=' '){
            //printf(":%d\n",i);
            if(s==0)
                s = 1;
            x = l[i++];
            lx+=s*w;
        }
        else{
            lc+=s*w;
        }
    }
    for(int i = 0;i<strlen(r);){
        int s = 0,w = 1;
        if(i >= strlen(r))
            break;
        while ((r[i] <= '0' || r[i] > '9')&&!((r[i]>='a')&&(r[i]<='z'))){
            if (r[i] == '-') 
                w = -1;
            i++;
        }
        while (r[i] >= '0' && r[i] <= '9') {
            s = s * 10 + r[i] - '0' ;
            i++;
        }
        if(i > strlen(r))
            break;
        if(r[i]!='-'&&r[i]!='+'&&r[i]!='\0'&&r[i]!=' '){
            if(s==0)
                s = 1;
            x = r[i++];
            rx+=s*w;
        }
        else{
            rc+=s*w;
        }
    }
    double ans = (rc-lc)/double(lx-rx);
    if(ans == -0)
        ans = 0;
    printf("%c=%.3lf\n",x,ans);
    return 0;
}