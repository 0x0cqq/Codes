#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string a,b;

void print(int b_1,int e_1,int b_2,int e_2){
    if(e_1-b_1<=0){
        return;
    }
    char x = b[e_2-1];
    printf("%c",x);
    for(int i = b_1;i<e_1;i++){
        if(a[i] == x){
            //cout << a.substr(b_1,i)<< endl;
            //cout << b.substr(b_2,i)<< endl;
            print(b_1,i,b_2,i-b_1+b_2);
            print(i+1,e_1,e_2-e_1+i,e_2-1);
            break;
        }
    }
}

int main(){
    cin >> a>> b;
    print(0,int(a.size()),0,int(a.size()));
    putchar('\n');
    return 0;
}