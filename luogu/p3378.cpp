#include <cstdio>
using namespace std;

int w[1010000];

int m,n = 0;

inline void qr(int &x){
    int f = 1,s = 0;char ch = getchar();
    while(ch<='0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    x = f*s;
}

void m_heap(int i){
    int l = (i<<1),r = (i<<1)+1;
    if(l>n){
        return;
    }
    else if(r>n){
        if(w[l]<w[i]){
            int tmp = w[l];
            w[l] = w[i];
            w[i] = tmp;
            m_heap(l);
        }
    }
    else{
        if(w[i]<=w[l]&&w[i]<=w[r])
            return;
        else{
            int m = w[l]<w[r]?l:r;
            int tmp = w[m];
            w[m] = w[i];
            w[i] = tmp;
            m_heap(m);
        }
    }
}

void m_heap2(int i){
    int t = i/2;
    if(w[t]>w[i]){
        int tmp = w[t];
        w[t] = w[i];
        w[i] = tmp;
        m_heap2(t);
    }
    return;
}

int main(){
    qr(m);
    for(int i = 0;i<m;i++){
        int a,b;
        qr(a);
        if(a == 1){
            qr(b);
            w[++n] = b;
            m_heap2(n);
        }
        else if(a == 2){
            printf("%d\n",w[1]);
        }
        else{
            w[1] = w[n--];
            m_heap(1);
        }
    }
    return 0;
}