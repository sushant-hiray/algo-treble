// w9 lexicographic-steps

#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include <cstring>
using namespace std;

//definitions
#define llu long long unsigned
#define lld long long
#define ld long

// fast I/O
#define getchar_unlocked() getchar()
#define putchar_unlocked(x) putchar(x)
//end of definitions

int scan_d() {register int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
ld scan_ld() {register int ip=getchar_unlocked(),flag=1;ld ret=0;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
lld scan_lld() {register int ip=getchar_unlocked(),flag=1;lld ret=0;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
llu scan_llu() {register int ip=getchar_unlocked();llu ret=0;for(;ip<'0'||ip>'9';ip=getchar_unlocked());for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return ret;}
 
//fast output
 
//no line break
void print_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<10);}
void print_ld(ld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=11;char output_buffer[11];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
void print_lld(lld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=21;char output_buffer[21];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<21);}
void print_llu(llu n) {int i=21;char output_buffer[21];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<21);}
 
//new line
void println_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
void println_ld(ld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=11;char output_buffer[12];output_buffer[11]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<12);}
void println_lld(lld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=21;char output_buffer[22];output_buffer[21]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<22);}
void println_llu(llu n) {int i=21;char output_buffer[22];output_buffer[21]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<22);}
 
//special char
char sp='/';
void printsp_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
void printsp_ld(ld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=11;char output_buffer[12];output_buffer[11]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<12);}
void printsp_lld(lld n) {if(n<0){n=-n;putchar_unlocked('-');}int i=21;char output_buffer[22];output_buffer[21]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<22);}
void printsp_llu(llu n) {int i=21;char output_buffer[22];output_buffer[21]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<22);}
 
inline void scan(string &ret){
    register int a=getchar_unlocked();
    ret="";
    while(a==' '||a=='\n'||a==EOF)
        a=getchar_unlocked();
    while(a!=' '&&a!='\n'&&a!=EOF){
        ret+=(char)a;
        a=getchar_unlocked();
    }
}

lld factorial(int n)
{
    lld ans = 1;
    for(int i = 2; i <= n; i++)
    {
        ans*=i;
    }
    return ans;
}

inline lld arrange(int h, int v)
{
    return factorial(h + v)/(factorial(h)*factorial(v));
}

void solve(lld k, int n, int m, lld add)
{
    if ((n <= 0) && (m <= 0))
        return;
    else if (n > 0)
    {
        lld temp = arrange(n-1, m);
        if (k<=(add + temp))
        {   
            cout << 'H';
            solve(k, n-1, m, add);
            return;
        } else {
            cout << 'V';
            solve(k, n, m - 1, add + temp);
            return;
        }
    } else if (m > 0) {
        cout << 'V';
        solve(k, n, m - 1, add);
        return;
    }
}

int main()
{
    int t, n, m;
    lld k;
    t = scan_d();
    while(t!=0) {
        n = scan_d();
        m = scan_d();
        k = scan_lld();
        solve(k+1, n, m, 0);
        cout << endl;
        t--;
    }
    return 0;
}
