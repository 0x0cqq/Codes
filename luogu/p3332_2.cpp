#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(ll &x){scanf("%lld",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 210000;
int n,m;
vector<int> num[MAXN];
vector<int> tmp;

int main(){
    read(n),read(m);
    int op,a,b;ll c;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b),read(c);
        if(op == 1)
            for(int i = a;i<=b;i++)
                num[i].push_back(int(c));
        else{
            for(int i = a;i<=b;i++){
                for(int j = 0;j<num[i].size();j++){
                    tmp.push_back(num[i][j]);
                }
            }
            sort(tmp.begin(),tmp.end(),[](const int &a,const int &b){return a > b;});
           /*for(auto i : tmp)
                printf("%d ",i);
            printf("\n");*/
            print(tmp[c-1]),print('\n');
            while(!tmp.empty()) tmp.pop_back();
        }
    }
    return 0;
}