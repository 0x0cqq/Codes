#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
typedef long long ll;  
int f[10][20];//f[i][j]表示以i开头的j位windy数有多少    
bool Conflict(int x)  
{  
    int temp=-10;  
    while(x)  
    {  
        if(abs(temp-x%10)<2)  
            return true;  
        temp=x%10;x/=10;  
    }  
    return false;  
}  
int Digital_DP(ll x)  
{  
    int i,j,re=0;  
    ll pos,now;  
    for(i=1,pos=10;pos<=x;i++,pos*=10)  
    {  
        for(j=1;j<=9;j++)  
            re+=f[j][i];  
    }  
    now=pos/=10;--i;  
    while(now<x)  
    {  
        while(now+pos<=x)  
        {  
            int temp=now/pos%10;  
            if( !Conflict(now/pos) )  
                for(j=0;j<=9;j++)  
                    if(abs(j-temp)>=2||pos==1)  
                        re+=f[j][i];  
            now+=pos;  
        }  
        if( Conflict(now/pos) )  
            break;  
        pos/=10;--i;  
          
    }  
    return re;  
}  
int main()  
{  
    int i,j,k;  
    f[0][0]=1;  
    for(i=0;i<=9;i++)  
        f[i][1]=1;  
    for(j=2;j<=10;j++)  
        for(i=0;i<=9;i++)  
            for(k=0;k<=9;k++)  
                if(abs(i-k)>=2)  
                    f[i][j]+=f[k][j-1];  
    int a,b;  
    cin>>a>>b;  
    cout<<Digital_DP(b+1)-Digital_DP(a)<<endl;  
}  