#include <cstdio>
using namespace std;

long long res[100][100][100];

long long s(long long a,long long b, long long c){
    if(a<=0||b<=0||c<=0)
        return 1;
    else if(a>20||b>20||c>20)
        return s(20,20,20);
    else if(res[a][b][c]){
        return res[a][b][c];
    }
    else{
        long long ans;
        if(a<b&&b<c)
            ans = s(a,b,c-1)+s(a,b-1,c-1)-s(a,b-1,c);
        else
            ans = s(a-1,b,c)+s(a-1,b-1,c)+s(a-1,b,c-1)-s(a-1,b-1,c-1);
        return res[a][b][c] = ans;
    }
}

int main(){
    while(true){
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        if(a==-1&&b==-1&&c==-1)
            break;
        printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,s(a,b,c));
    }
    return 0;
}