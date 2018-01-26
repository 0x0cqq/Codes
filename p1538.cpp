#include <cstdio>
#include <cstring>
using namespace std;

char x[1000];
int l;

bool heng1[10] = {1,0,1,1,0,1,1,1,1,1};
bool heng2[10] = {0,0,1,1,1,1,1,0,1,1};
bool heng3[10] = {1,0,1,1,0,1,1,0,1,1};
bool shu1[10]  = {1,0,0,0,1,1,1,0,1,1};
bool shu2[10]  = {1,1,1,1,1,0,0,1,1,1};
bool shu3[10]  = {1,0,1,0,0,0,1,0,1,0};
bool shu4[10]  = {1,1,0,1,1,1,1,1,1,1};


int main(){
    scanf("%d",&l);
    scanf("%s",x);
    for(int i = 0;i<strlen(x);i++){
        if(heng1[x[i]-48]){
            putchar(' ');
            for(int i = 0;i<l;i++)
                putchar('-');
            putchar(' ');
            putchar(' ');
        }
        else
            for(int i = 0;i<l+3;i++)
                putchar(' ');
    }
    putchar('\n');
    
    for(int k = 0;k<l;k++){
        for(int i = 0;i<strlen(x);i++){
            if(shu1[x[i]-48] == 1)
                putchar('|');
            else
                putchar(' ');
            for(int i = 0;i<l;i++)
                putchar(' ');
            if(shu2[x[i]-48] == 1)
                putchar('|');
            else
                putchar(' ');
            putchar(' ');
        }  
        putchar('\n');
    }
    
    for(int i = 0;i<strlen(x);i++){
        if(heng2[x[i]-48]){
            putchar(' ');
            for(int i = 0;i<l;i++)
                putchar('-');
            putchar(' ');
            putchar(' ');
        }
        else
            for(int i = 0;i<l+3;i++)
                putchar(' ');
    }
    putchar('\n');

    for(int k = 0;k<l;k++){
        for(int i = 0;i<strlen(x);i++){
            if(shu3[x[i]-48] == 1)
                putchar('|');
            else
                putchar(' ');
            for(int i = 0;i<l;i++)
                putchar(' ');
            if(shu4[x[i]-48] == 1)
                putchar('|');
            else
                putchar(' ');
            putchar(' ');
        }  
        putchar('\n');
    }

    for(int i = 0;i<strlen(x);i++){
        if(heng3[x[i]-48]){
            putchar(' ');
            for(int i = 0;i<l;i++)
                putchar('-');
            putchar(' ');
            putchar(' ');
        }
        else
            for(int i = 0;i<l+3;i++)
                putchar(' ');
    }
    putchar('\n');
    return 0;
}