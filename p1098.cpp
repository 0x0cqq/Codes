#include <cstdio>
#include <cstring>
using namespace std;

char k[1000];

int main(){
    int p1,p2,p3,l;
    scanf("%d %d %d ",&p1,&p2,&p3);
    scanf("%[^\n]",k);
    l = strlen(k);
    for(int i = 0;i<l;i++){
        if(k[i+1]!='-'||k[i]=='-'&&k[i+1]=='-')
            putchar(k[i]);
        else if(k[i]>=k[i+2]||(48<=k[i]&&k[i]<=57&&97<=k[i+2]&&k[i+2]<=122)){
            putchar(k[i++]);
            putchar(k[i]);
        }
        else if(p3==2){
            putchar(k[i]);
            for(int j = k[i+2]-1;j>k[i];j--){
                for(int w = 0;w<p2;w++){
                    if(p1==1) putchar(j);
                    else if(p1==3) putchar('*');
                    else{
                        if('0'<=j&&j<='9') putchar(j);
                        else putchar(j-32);
                    }
                }
            }
            i+=1;
        }
        else{
            putchar(k[i]);
            for(int j = k[i]+1;j<k[i+2];j++){
                for(int w = 0;w<p2;w++){
                    if(p1==1) putchar(j);
                    else if(p1==3) putchar('*');
                    else{
                        if('0'<=j&&j<='9') putchar(j);
                        else putchar(j-32);
                    }
                }
            }
            i+=1;
        }
    }
    putchar('\n');
    return 0;
}