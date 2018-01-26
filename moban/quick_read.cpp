#include <cstdio>
using namespace std;

int quick_read(){
    int f = 1,s = 0;char c = getchar();
    while(c<='0'||c>'9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    return f*s;
}

int main(){
    int x = quick_read();
    printf("%d\n",x);
    return 0;
}