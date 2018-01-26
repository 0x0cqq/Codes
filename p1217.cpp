#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

bool p[10000100];

void prime(int k){
    memset(p,1,k+1);
    p[1] = 0;
    for(int i = 2;i<=(k+1)/2;i++)
        if(p[i]){
            int t = 2*i;
            while(t<=k+1){
                p[t] = 0;
                t+=i;
            }
        }
}


bool is_huiwen(string a){
    for(int i = 0;i<a.size();i++){
        if(a[i]!=a[a.size()-i-1])
            return false;
        if(i>a.size()-i-1)
            return true;
    }
    return true;
}

int main(){
    //freopen("4.txt","w",stdout);
    int a,b;
    scanf("%d %d",&a,&b);
    if(b>10000000)
        b = 10000000;
    prime(10000000);
    //printf("%d %d\n",is_huiwen(a),is_huiwen(b));
    for(int i = a;i<b;i++){
        if(p[i]&&is_huiwen(to_string(i)))
            printf("%d\n",i);
    }
    return 0;
}
