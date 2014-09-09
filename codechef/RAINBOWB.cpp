// RAINBOWB

#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
using namespace std;

//definitions
#define llu long long unsigned
#define lld long long
#define ld long
#define MODN 1000000007
// fast I/O
#define gc_unlocked() getchar()
#define pc_unlocked(x) putchar(x)
//end of definitions

int scan_d() {register int ip=gc_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=gc_unlocked())if(ip=='-'){flag=-1;ip=gc_unlocked();break;}for(;ip>='0'&&ip<='9';ip=gc_unlocked())ret=ret*10+ip-'0';return flag*ret;}
ld scan_ld() {register int ip=gc_unlocked(),flag=1;ld ret=0;for(;ip<'0'||ip>'9';ip=gc_unlocked())if(ip=='-'){flag=-1;ip=gc_unlocked();break;}for(;ip>='0'&&ip<='9';ip=gc_unlocked())ret=ret*10+ip-'0';return flag*ret;}
lld scan_lld() {register int ip=gc_unlocked(),flag=1;lld ret=0;for(;ip<'0'||ip>'9';ip=gc_unlocked())if(ip=='-'){flag=-1;ip=gc_unlocked();break;}for(;ip>='0'&&ip<='9';ip=gc_unlocked())ret=ret*10+ip-'0';return flag*ret;}
llu scan_llu() {register int ip=gc_unlocked();llu ret=0;for(;ip<'0'||ip>'9';ip=gc_unlocked());for(;ip>='0'&&ip<='9';ip=gc_unlocked())ret=ret*10+ip-'0';return ret;}
 
//fast output
 
//no line break
void print_d(int n) {if(n<0){n=-n;pc_unlocked('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<10);}
void print_ld(ld n) {if(n<0){n=-n;pc_unlocked('-');}int i=11;char output_buffer[11];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<11);}
void print_lld(lld n) {if(n<0){n=-n;pc_unlocked('-');}int i=21;char output_buffer[21];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<21);}
void print_llu(llu n) {int i=21;char output_buffer[21];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<21);}
 
//new line
void println_d(int n) {if(n<0){n=-n;pc_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<11);}
void println_ld(ld n) {if(n<0){n=-n;pc_unlocked('-');}int i=11;char output_buffer[12];output_buffer[11]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<12);}
void println_lld(lld n) {if(n<0){n=-n;pc_unlocked('-');}int i=21;char output_buffer[22];output_buffer[21]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<22);}
void println_llu(llu n) {int i=21;char output_buffer[22];output_buffer[21]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<22);}
 
//special char
char sp='/';
void printsp_d(int n) {if(n<0){n=-n;pc_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<11);}
void printsp_ld(ld n) {if(n<0){n=-n;pc_unlocked('-');}int i=11;char output_buffer[12];output_buffer[11]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<12);}
void printsp_lld(lld n) {if(n<0){n=-n;pc_unlocked('-');}int i=21;char output_buffer[22];output_buffer[21]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<22);}
void printsp_llu(llu n) {int i=21;char output_buffer[22];output_buffer[21]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc_unlocked(output_buffer[i]);}while(++i<22);}
 
inline void scan(string &ret){
    register int a=gc_unlocked();
    ret="";
    while(a==' '||a=='\n'||a==EOF)
        a=gc_unlocked();
    while(a!=' '&&a!='\n'&&a!=EOF){
        ret+=(char)a;
        a=gc_unlocked();
    }
}

inline lld mod(lld x)
{
    if (x < MODN)
        return x;
    else
        return x % MODN;
}

inline lld multiply(lld x, lld y)
{
    x = mod(x);
    y = mod(y);
    return mod(x*y);
}


lld degree(lld a, lld k) {
  lld res = 1;
  lld cur = a;
  while (k) {
    if (k%2) {
      res = multiply(res, cur);
    }
    k /= 2;
    cur = multiply(cur, cur);
  }
  return res;
}

lld nck(lld n, lld k)
{
	lld num = 1;
	if (n < k)
		return 1;
	for (lld i = n; i > n- k; --i) {
	  num = multiply(num, i);
	}
	lld den = 1, ti;
	for (lld i = 1; i <=k; ++i)
	{
		ti = i;
	    while(mod(ti) == 0) {
	      ti /= MODN;
	    }
	    den = multiply(den, ti);
	}
	// cout << "Num is "<<num << " "<< den << endl;
	return multiply(num, degree(den, MODN - 2));
}

int main()
{
	lld n,i=1,count = 0,temp;
	n = scan_lld();
	while(i <= n - 12)
	{
		// cout << i <<endl;
		temp = n - i;
		if (temp%2 == 1) {
			i++;
			continue;
		}
		temp /= 2;
		temp -= 6;
		if (temp >= 0)
		{
			// cout << "here " <<temp << endl;
			count = count + nck(temp + 5, 5)%MODN;
			count = count%MODN;
		}
		i++;
	}
	println_lld(count);
}