#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct bigint{
    int x[10000];size_t n = 0;
    void operator =(const bigint b){
        memcpy(this,&b,sizeof(b));
    }
    void operator =(const int a){
        memset(x,0,4000);
        int t = a,i = 0;
        while(t>0){
            x[i] = t%10000;
            t/=10000;
            n++;i++;
        }
    }
    void operator =(const string c){
        memset(x,0,4000);
        string a = c;
        int t = 0;
        while(a[t]=='0'){
            t++;
            if(t == a.size()){
                n = 1;
                x[0] = 0;
                return;
            }
        }
        a.erase(0,t);
        for(int i = a.size()-1,j = 0;i>=0;i--,j++){
            x[j/4]+=(a[i]-48)*pow(10,j%4);
            //printf("%d\n",x[j/4]);
        }
        n = (a.size()-1)/4+1;
    }
    bigint operator +(const bigint a)const{
        bigint c;
        int plus = 0;
        c.n = max(n,a.n);
        for(int i = 0;i<c.n;i++){
            plus = (c.x[i]=x[i]+a.x[i]+plus)/10000;
            c.x[i] %= 10000;
            //printf("plus:%d,number:%d\n",plus,c.x[i]);
        }
        if(plus!=0){
            c.x[n] = plus;
            c.n++;
        }
        return c;
    }
    bigint operator *(const int a)const{
        bigint c;
        c.n = n;
        int plus = 0;
        for(int i = 0;i<n;i++){
            c.x[i] = (x[i]*a+plus)%10000;
            plus = (x[i]*a+plus)/10000;
            //printf("plus:%d\n",plus);
        }
        if(plus!=0){
            c.x[n] = plus;
            c.n++;
        }
        return c;
    }
    bigint operator /(const int a)const{
        bigint c;
        c.n = n;
        for(int i = n-1,s = 0;i>=0;i--){
            s = s*10000+x[i];
            c.x[i] = s/a;
            s = s%a;
            if(c.x[i] == 0)
                c.n--;
        }
        if(c.n==0){
            c.x[0] = 0;
            c.n = 1;
        }
        return c;
    }
    bool operator <(const bigint a)const{
        if(n>a.n)
            return false;
        else if(n<a.n)
            return true;
        else{
            for(int i = n-1;i>=0;i--){
                if(x[i]>a.x[i])
                    return false;
                else if(x[i]<a.x[i])
                    return true;
            }
            return false;
        }
    }
    void print(){
        for(int i = n-1;i>=0;i--){
            if(i == n-1)
                printf("%d",x[i]);
            else
                printf("%04d",x[i]);
        }
        printf("\n");        
    }
}b_p[1005],after[1005];



struct people{
    int l,r;
    bool operator <(const people &a)const{
        return l*r<a.l*a.r;
    }   
}p[1005];

int main(){
    int n;
    scanf("%d",&n);
    scanf("%d %d",&(p[0].l),&(p[0].r));
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&(p[i].l),&(p[i].r));
    }
    sort(p+1,p+n+1);
    b_p[0] = p[0].l;
    for(int i = 1;i<=n;i++){
        if(i == 1)
            b_p[i] = b_p[0];
        else{
            b_p[i] = b_p[i-1]*p[i-1].l;
        }
    }
    for(int i = 1;i<=n;i++){
        after[i] = b_p[i]/p[i].r;
    }
    sort(after+1,after+n+1);
    /*for(int i = 1;i<=n;i++){
        printf("\n:%d %d\n",p[i].l,p[i].r);
        b_p[i].print();
        after[i].print();
    }*/
    after[n].print();
    //system("pause");
    return 0;
}
