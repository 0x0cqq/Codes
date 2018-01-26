#include <cstdio>
#include <cstring>
using namespace std;


struct Student{
    int num,age;
    char id[20];
};

void mergesort(Student *s,int num){
    if(num>1){
        Student T1[num/2],T2[num-num/2];
        for(int i = 0;i<num/2+1;i++){
            if(i<num/2) T1[i] = s[i];
            if(num/2+i < num && i<num-num/2) T2[i] = s[(num/2)+i];
        }
        mergesort(T1,num/2);
        mergesort(T2,num-num/2);
        int t1 = 0,t2 = 0;
        for(int i = 0;i<num;i++){
            if(t1<num/2&&t2<num-num/2){
                if(T1[t1].age>T2[t2].age) s[i] = T1[t1++];
                else if(T1[t1].age<T2[t2].age) s[i] = T2[t2++];
                else if(T1[t1].num<T2[t2].num) s[i] = T1[t1++];
                else s[i] = T2[t2++];
            }   
            else if(t1 == num/2) s[i]=T2[t2++];
            else if(t2 == num-num/2) s[i]=T1[t1++];
        }
    }
}

int main(){
    int n,y = 0,o = 0;
    scanf("%d",&n);
    Student young[n],old[n];
    for(int i = 0;i<n;i++){
        Student t;
        scanf("%s %d",t.id,&(t.age));
        t.num = i;
        if(t.age>=60)
            old[o++] = t;
        else
            young[y++] = t;
    }
    mergesort(old,o);
    for(int i = m-1;i<n;m++){
        if(stu[m].s != stu[i].s)
        break;
    }
    printf("%d %d\n",stu[m-1].s,m);
    for(int i = 0;i<m;i++)
        printf("%d %d\n",stu[i].id,stu[i].s);
    return 0;
}