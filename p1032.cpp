#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

struct bianhuan
{
    string a,b;
}bi[100];

struct node{
    string str;
    int nown;
};

queue<node> x;
set<string> f;

int N = 0,X = 0;
string A,B,TA,TB;


int main(){
    cin >> A >> B;
    while(cin >> TA >>TB){
        if(TA!=TB){
            bi[N].a = TA;bi[N].b = TB;
            //printf("%s %s\n",bi[N].a.c_str(),bi[N].b.c_str());
            N++;
        }
    }
    //printf("Get!!!!!!\n");
    node ne;
    ne.str = A;
    ne.nown = 0;
    x.push(ne);
    while(!x.empty()){
        node tmp = x.front();
        x.pop();
        if(tmp.nown>=11){
            printf("NO ANSWER!\n");
            return 0;
        }
        else if(tmp.str==B){
            //cout<< tmp.str << endl;
            //printf("!!!!!!");
            printf("%d\n",tmp.nown);
            return 0;
        }
        else{
            for(int w = 0;w<N;w++)
                if(tmp.str.find(bi[w].a)!=tmp.str.size())
                    for(auto i = 0;i<=int(tmp.str.size()-bi[w].a.size());i++)
                        if(tmp.str.substr(i,bi[w].a.size())==bi[w].a){
                            node need = tmp;
                            need.str.replace(i,bi[w].a.size(),bi[w].b);
                            if(f.count(need.str))
                                continue;
                            f.insert(need.str);
                            need.nown++;
                            x.push(need);
                        }
        }
    }
    printf("NO ANSWER!\n");
    return 0;
}