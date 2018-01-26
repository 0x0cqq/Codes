#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Stu{
    char name[50];
    int score_1, score_2, paper;
    bool iswest, s_off;
    int m;
    int calculate(){
        int money = 0;
        if(score_2>80&&s_off)
            money+=850;
        if(score_1>85&&iswest)
            money+=1000;
        if(score_1>90)
            money+=2000;
        if(score_1>85&&score_2>80)
            money+=4000;
        if(score_1>80&&paper>0)
            money+=8000;
        return money;
    }
};

int main(){
    int n,ans=0,max = -1;
    char na[50];
    scanf("%d",&n);
    getchar();
    vector<Stu> students;
    for(int i = 0 ;i < n;i++){
        Stu tmp;
        char d ='\n';
        char str[1000],a,b;;
        if(getline(&str,&d,stdin)==0)
            break;
        sscanf(str,"%s %d %d %s %s %d",tmp.name,&(tmp.score_1),&(tmp.score_2),&a,&b,&(tmp.paper));
        tmp.iswest = (b == 'Y')?1:0;
        tmp.s_off = (a == 'Y')?1:0;
        tmp.m = tmp.calculate();
        students.push_back(tmp);
    }
    
    for(int i = 0;i<students.size();i++){
        if(students[i].m>max){
            memcpy(na,students[i].name,50);
            max = students[i].m;
        }
            ans+=students[i].m;
            printf("%d\n",ans);
    }
    printf("%s\n%d\n%d\n",na,max,ans);
    return 0;
}