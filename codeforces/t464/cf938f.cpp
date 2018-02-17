#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string a;

int main(){
    cin >> a;
    int k = 1;
    while(k< a.size()){
        k <<= 1;
    }
    k >>=1 ;
    for(;k;k>>=1){
        for(int i = 0;i<=a.size()-k;i++){
            
        }
    }
    return 0;
}