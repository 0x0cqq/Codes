#include <cstdio>
#include <stack>
#include <cstdlib>
#include <unistd.h>
using namespace std;

struct ob{
    bool f;//0 +-*/ , 1 numbers
    double num;
    char l;
    ob(bool fl,char leixing = 0,double number = 0):f(fl),num(number),l(leixing){}
};

stack<ob> s;

int main(){
    double t;
    while(!(s.size() == 1 && s.top().f == 1)){
        if(scanf("%lf ",&t) != 1){
            char c = getchar();
            while(c == ' '||c=='\n') c = getchar();
            getchar();
            ob tem = ob(0,c);
            if(c == -1)
                break;
            printf("%d\n",c);
            s.push(tem);
            sleep(1);
        }
        else{
            sleep(1);
            printf("22222\n");
            ob tem = ob(1,0,t);
            s.push(tem);
        }
        printf("t:%lf\n",t);
        printf("%d %lf\n",s.top().f,s.top().num);
    }
    while(s.size()>=3){
        ob t1 = s.top();
        s.pop();
        ob t2 = s.top();
        s.pop();
        ob t3 = s.top();
        s.pop();
        ob need = ob(1);
        if(t3.l == '+')
            need.num = t1.num+t2.num;
        else if(t3.l == '-')
            need.num = t1.num-t2.num;
        else if(t3.l == '*')
            need.num = t1.num*t2.num;
        else if(t3.l == '/')
            need.num = t1.num/t2.num;
        s.push(need);
        sleep(1);
        printf("%lf\n",s.top().num);
    }
    printf("%lf\n",s.top().num);
    return 0;
}