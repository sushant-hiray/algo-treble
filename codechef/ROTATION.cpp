// ROTATION

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

void print(std::vector<int> v)
{
	for(int i=0; i<v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	int n, m;
	n = scan_d();
	m = scan_d();
	std::vector<int> v(n);
	for(int i=0; i < n; i++)
	{
		v[i] = scan_d();
	}
	int offset=0;
	char d;
	int s;
	int temp;
	while(m--) {
		cin >> d;
		cin >> s;
		if (d == 'R') {
			temp = (offset + s - 1)%n;
			if (temp<0)
				println_d(v[(temp+n)%n]);
			else
				println_d(v[temp]);
		}
			
		else if (d == 'C')
			offset+=s;
		else if (d == 'A')
			offset-=s;
	}


}