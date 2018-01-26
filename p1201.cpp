#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct people{
    string name;
    int money;
}k[20];

int n;

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        cin >> k[i].name;
    }
    for(int i = 0;i<n;i++){
        string tmp;
        cin >> tmp;
        for(int i = 0;i<n;i++){
            if(k[i].name!=tmp)
                continue;
            int m,p;
            scanf("%d %d",&m,&p);
            for(int w = 0;w<p;w++){
                string t;
                cin >> t;
                for(int j = 0;j<n;j++){
                    if(k[j].name==t){
                        //printf(":%d %d %d\n",i,j,m/p);
                        k[j].money+=m/p;
                        k[i].money-=m/p;
                    }
                }
            }
            break;
        }
    }
    for(int i = 0;i<n;i++){
        cout << k[i].name;
        printf(" %d\n",k[i].money);
    }
    return 0;
}