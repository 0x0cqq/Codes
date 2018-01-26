#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct bigint{
    int x[10000];size_t n = 0;bool flag = 1;
    void operator =(const bigint b){
        memcpy(this,&b,sizeof(b));
    }
    void operator =(const int a){
        memset(x,0,sizeof(x));
        int t = abs(a),i = 0;
        flag = a>=0?1:0;
        while(t>0){
            x[i] = t%10000;
            t/=10000;
            n++;i++;
        }
    }
    void operator =(const string c){
        memset(x,0,sizeof(x));
        string a = c;
        int t = 0;
        while(a[t]<'0'||a[t]>'9')
            if(a[t++] == '-')
                flag = 0;
        while(a[t]=='0'){
            if(t == a.size()){
                n = 1;
                return;
            }
            t++;
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
    bigint operator -(const bigint a)const{
        bigint c;
        bigint d;
        memcpy(&d,this,sizeof(*(this)));
        bigint b = a;
        b.flag = !b.flag;
        c = d + b;
        return c;
    }
    bigint operator *(const int t)const{
        bigint c;
        c.n = n;
        int plus = 0,a = abs(t);
        bool f = t >=0?1:0;
        for(int i = 0;i<n;i++){
            c.x[i] = (x[i]*a+plus)%10000;
            plus = (x[i]*a+plus)/10000;
            //printf("plus:%d\n",plus);
        }
        if(plus!=0){
            c.x[n] = plus;
            c.n++;
        }
        c.flag = !(flag^f);
        return c;
    }
    bigint operator /(const int t)const{
        bigint c;
        c.n = n;
        int a = abs(t);
        bool f = t>=0?1:0;
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
        c.flag = !(flag^f);
        return c;
    }
    bool operator <(const bigint a)const{
        if(flag<a.flag)
            return true;
        else if (flag>a.flag)
            return false;
        if(n>a.n)
            return !(false^flag);
        else if(n<a.n)
            return !(true^flag);
        else{
            for(int i = n-1;i>=0;i--){
                if(x[i]>a.x[i])
                    return !(false^flag);
                else if(x[i]<a.x[i])
                    return !(true^flag);
            }
            return false;
        }
    }
    void print(){
        if(n == 0&&x[0] == 0){
            printf("0\n");
            return;
        }
        if(flag == 0)
            putchar('-');
        for(int i = n-1;i>=0;i--){
            if(i == n-1)
                printf("%d",x[i]);
            else
                printf("%04d",x[i]);
        }
        printf("\n");        
    }
};



int main(){
    string a;int b;
    cin >> a;
    getchar();
    cin >> b;
    bigint c,d,e;
    c = a;d = b;
    //c.print();
    //d.print();
    //c.print();
    e  = c+d;
    e.print();
    //system("pause");
    return 0;
}
