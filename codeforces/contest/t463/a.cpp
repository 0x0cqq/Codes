#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

string a;

int main(){
    cin >> a;
    cout << a;
    for(int i = a.size()-1;i>=0;i--){
        putchar(a[i]);
    }
    putchar('\n');
    return 0;
}