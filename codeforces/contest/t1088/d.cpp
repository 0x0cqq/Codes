#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310000;

void ff(){fflush(stdout);}

int n;
int num[MAXN][2];
int com[MAXN];

int flag = 0;// 上一位(整个数)的大小关系

int nowa = 0,nowb = 0;// 已经知道的 a b 的大小


void getans(int i){
  if(i == -1){return;}
  int f1,f2;//0X 0Y / 0X 1Y / 1X 0Y / 1X 1Y 
  printf("? %d %d\n",nowa,nowb + (1<<i));ff();// 对 b 的这一位取反
  scanf("%d",&f1);
  printf("? %d %d\n",nowa + (1<<i)-1,nowb + (1<<i)-1);ff();// 取反 X Y 判断第 i 位是否相同
  scanf("%d",&f2);
  // printf("---flag:%d\n",flag);
  if(flag == 0){
    if(f1 == 1)
      nowa += (1<<i),nowb += (1<<i);
    else if(f1 == -1)
      nowa += 0,nowb += 0;
  }
  else if(flag == -1){
    if(f1 == -1){//0,1 / 0,0
      if(f2 == -1){nowa += 0,nowb += (1<<i);flag = -1;}
      else if(f2 == 1){nowa += 0,nowb += 0;flag = -1;}
      else{}
    }
    else if(f1 == 1){//1,1 / 0,1
      if(f2 == -1){nowa += 0,nowb += (1<<i);flag = 1;}
      else if(f2 == 1){nowa += (1<<i),nowb += (1<<i);flag = -1;}
      else{}
    }
    else{
      nowa += 0,nowb += (1<<i);
      flag = 0;
    }
  }
  else if(flag == 1){ // ?X > ?Y
    if(f1 == -1){ //1,0 / 0,0
      if(f2 == -1){nowa += 0,nowb += 0;flag = 1;}
      else if(f2 == 1){nowa += (1<<i),nowb += 0;flag = -1;}
      else{}
    }
    else if(f1 == 1){//1,0 / 1,1
      if(f2 == -1){nowa += (1<<i),nowb += (1<<i);flag = 1;}
      else if(f2 == 1){nowa += (1<<i),nowb += 0;flag = 1;}
      else{}
    }
    else{
      nowa += (1<<i),nowb += 0;
      flag = 0;
    } 
  }
  // printf("nowa:%d nowb:%d flag:%d\n",nowa,nowb,flag);
  getans(i-1);
}

int main(){
  printf("? 0 0\n");ff();
  scanf("%d",&flag);
  getans(29);
  printf("! %d %d\n",nowa,nowb);
  return 0;
}