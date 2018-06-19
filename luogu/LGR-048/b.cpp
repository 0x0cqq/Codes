#include <cstdio>
#include <map>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

map<string,double> m = {
{"H",1},
{"C",12},
{"N",14},
{"O",16},
{"F",19},
{"Na",23},
{"Mg",24},
{"Al",27},
{"Si",28},
{"P",31},
{"S",32},
{"Cl",35.5},
{"K",39},
{"Ca",40},
{"Mn",55},
{"Fe",56},
{"Cu",64},
{"Zn",65},
{"Ag",108},
{"I",127},
{"Ba",137},
{"Hf",178.5},
{"Pt",195},
{"Au",197},
{"Hg",201}
};

double get_ans(char*&);
double get_num(char* &);
double get_yuanzi(char* &);
double get_part(char* &);

const int MAXN = 10000;
char s[MAXN];
char *t = s;


double get_yuanzi(char* &w){
    char tt[23];
    tt[0] = w[0];
    w++;
    tt[1] = 0;
    while(*w>='a' && *w<='z')
        tt[1] = w[0],w++;
    tt[2] = 0;
    //printf("tt:%s\n",tt);
    return m[string(tt)];
}

double get_part(char* &w){
    if(*w!='('){
        double ans = 0;
        ans += get_yuanzi(w) * get_num(w);
        return ans;
    }
    else{
        w++;
        double ans = 0;
        while(*w!='~' && *w && *w != ')'){
            double tmp = get_part(w);
            // printf("now:%c\n",*w);
            ans += tmp * get_num(w);
        }
        w++;
        return ans;
    }
}

double get_num(char* &w){
    double ans = 0;
    if(*w!='_')
        return 1;
    sscanf(w+2,"%lf",&ans);
    // printf("%lf\n",ans);
    while(*w!='}')
        w++;
    w++;
    return ans;
}

double get_ans(char* &w){
    double ans = 0;
    while(*w!='~' && *w){
        double tmp = get_part(w);
        ans += tmp * get_num(w);
    }
    if(*w == '~'){
        int tmp = 0;
        w++;
        if(!isdigit(*w))
            tmp = 1;
        else
            sscanf(w,"%d",&tmp);
        ans += 18*tmp;
    }
    w++;
    return ans;
}


int main(){
    scanf("%s",s);
    printf("%g\n",get_ans(t));
    return 0;
}