#include <cstdio>
using namespace std;

char k[1000000];

int main(){
    char x;
    int w=0,l=0,i=0;
    scanf("%[^E]",k);
    while(true){
        x=*(k+i++);
        if(x=='W') w++;
        else if(x=='L') l++;
        else if(x==0){
            printf("%d:%d\n",w,l);
            w = l = 0;
            break;
        }
        else continue;
        if((w>=11&&w-1>l)||(l>=11&&l-1>w)){
            printf("%d:%d\n",w,l);
            w = l = 0;
        }
    }
    printf("\n");
    i=0;
    while(true){
        x=*(k+i++);
        if(x=='W') w++;
        else if(x=='L') l++;
        else if(x==0){
            printf("%d:%d\n",w,l);
            w = l = 0;
            break;
        }
        else continue;
        if((w>=21&&w-1>l)||(l>=21&&l-1>w)){
            printf("%d:%d\n",w,l);
            w = l = 0;
        }
    }
    return 0;
}