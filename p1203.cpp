#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char k[1000];
int l,ans = 0;

int search(int pos){
    //printf("%d:",pos);
    int npos = pos+l-1;
    int res = 0;
    int mubiao = k[pos]=='r'?1:k[pos]=='b'?-1:0;;
    for(int i = pos;i<npos;i++){
        int nowmubiao = k[i]=='r'?1:k[i]=='b'?-1:0;;
        if(nowmubiao != 0 && mubiao==0)
            mubiao = k[i]=='r'?1:k[i]=='b'?-1:0;;
        
        if(nowmubiao == mubiao||nowmubiao == 0){
            pos = i;
            res++;
        }
        else{
            break;
        }
    }
    //printf("%d ",pos);
    mubiao = k[npos]=='r'?1:k[npos]=='b'?-1:0;;
    for(int i = npos;i>pos;i--){
        int nowmubiao = k[i]=='r'?1:k[i]=='b'?-1:0;;
        if(nowmubiao != 0 && mubiao==0)
            mubiao = k[i]=='r'?1:k[i]=='b'?-1:0;;
        if(nowmubiao == mubiao||nowmubiao == 0)
            res++;
        else
            break;
    }
    //printf("%d\n",res);
    return res;
}

int main(){
    scanf("%d ",&l);
    scanf("%s",k);//r +,b -
    l = strlen(k);
    memcpy(k+l,k,l);
    //printf("%s\n",k);
    for(int i = 0;i<l;i++)
        ans = max(ans,search(i));
    printf("%d\n",ans);
    return 0;
}