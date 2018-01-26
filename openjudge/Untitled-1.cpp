#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;


int main(){
    string a = "abcdefg";
    string b = "bbcdef";
    cout << (a.find(b) == -1);
    return 0;
}