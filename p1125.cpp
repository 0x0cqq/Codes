#include <cstdio>
#include <cstring>
using namespace std;

bool p(int x){
    if(x==0||x==1)
        return false;
    for(int i = 2;i<x;i++)
        if(x%i==0)
            return false;
    return true;
}
int w[26];

int main(){
    char k[100];
    scanf("%s",k);
    for(int i = 0;i<strlen(k);i++)
        w[k[i]-97]++;
    int max = -1,min = 100;
    for(int i = 0;i<26;i++)
        if(w[i]){
            w[i]>max?max = w[i]:0;
            w[i]<min?min = w[i]:0;
        }
    int t = max - min;
    if(p(t))
        printf("Lucky Word\n%d\n",t);
    else
        printf("No Answer\n0\n");
    return 0;
}