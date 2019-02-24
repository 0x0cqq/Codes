#include <cstdio>
#define inf 1e18
using namespace std;

FILE *in,*o1,*o2,*a1;
void file_open(){
  in = fopen("in.txt","r");
  o1 = fopen("out1.txt","r");
  o2 = fopen("out2.txt","r");
  a1 = fopen("diff.txt","w");
}
void file_close(){
  fclose(in);
  fclose(o1);
  fclose(o2);
  fclose(a1);
}


int diff(){
  return system("diff out1.txt out2.txt > /dev/null 2>&1");
}

void check(){
  return diff();
}


int main(){
  file_open();
  int t = check();
  fprintf(a1,"RESULT:%d\n",t);
  file_close();
  return t;
  return diff();
}