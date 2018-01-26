#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Bigint
{
    int num[100];
    Bigint();
    Bigint(string a){
        char tmp[5];
        memset(tmp,0,5);
        for(int n = 0;n<ceil(strlen(a.c_str())/4)*4;n++){
                tmp[n%4] = a[n];
            if(n%4 == 3)
                num[n/4] = atoi(tmp);
        }
    }
    Bigint operator + (Bigint &a){
        Bigint b;
        for(int i = 0;i<99;++i){
            b.num[i] = (a.num[i]+num[i])%10000;
            b.num[i+1] = (a.num[i]+num[i])%10000;
        }
        return b;
    }

};

int main(){
    string str;
    cin >> str;
    Bigint a(str);

    return 0;
}