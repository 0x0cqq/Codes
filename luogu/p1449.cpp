#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;


int main(){
    char k[10000];
    scanf("%s",k);
    stack<int> s;
    char x;int t = 0;
    for(int i = 0;k[i]!='@'&&i<strlen(k);i++){
        x = k[i];
        if(x == '+'||x == '-'||x == '*'||x == '/'){
            int b = s.top();
            s.pop();
            int a = s.top();
            int w;
            s.pop();
            switch(x){
                case '+':
                    w = a+b;
                    break;
                case '-':
                    w = a-b;
                    break;
                case '*':
                    w = a*b;
                    break;
                case '/':
                    w = a/b;
                    break;
            }
            s.push(w);
            //printf("!%d\n",w);
        }
        else if(k[i]!='.'){
            t*=10;
            t+=k[i]-48;
        }
        else{
            s.push(t);
            //printf(":%d\n",t);
            t = 0;
        }
    }
    printf("%d\n",s.top());
    return 0;
}