#include <cstdio>
#include <cctype>

namespace fast_io {
    inline char read(){
		//return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))== s)?-1:*s++) : *s++;
    }
    inline void read(int &x){
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            x = ((x+(x<<2))<<1) + (c ^ '0');
        if (iosig) x = -x;
    }
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c!='\r'||c =='\n'))
            c = read();
        while(c!= -1&&c!=' '&&c!='\r'&&c!='\n')
            *a++ = c,c = read();
        *a = 0;
    }
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c){
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x){
        static int buf[30], cnt;
        if (x == 0)
            print('0');
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    inline void print(char *a){
        while(*a) print(*a++);
    }
    inline void flush(){
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

namespace normal_io{
    inline char read(){
        return getchar();
    }
    inline void read(int &x){
        scanf("%d",&x);
    }
    inline void print(int x){
        printf("%d",x);
    }
    inline void print(char x){
        putchar(x);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

int main(){
    int x;
    read(x);
    print(x);
    flush();
    return 0;
}