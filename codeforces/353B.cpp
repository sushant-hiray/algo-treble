// 353B
#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <utility>

//definitions
#define llu long long unsigned
#define lld long long
#define ld long

#define getchar_unlocked() getchar()
#define putchar_unlocked(x) putchar(x)
//end of definitions
 

using namespace std;

int scan_d() {register int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
//fast output
 
//no line break
void print_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<10);}
 
//new line
void println_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]='\n';do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
 
//special char
char sp='/';
void printsp_d(int n) {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[11];output_buffer[10]=sp;do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<11);}
 
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

vector<pair<int, int> >v;
vector<int> f;
int n;
bool sort_f (pair<int, int> i, pair<int, int> j) { return (i.first<j.first); }
bool sort_s (pair<int, int> i, pair<int, int> j) { return (j.first<i.first); }

int get_range(int i)
{
    int count = 0;
    int j=i+1;
    i = v[i].first;
    while(j < 2*n) {
        if(v[j].first == i) {
            count++;
        } else {
            break;
        }
        j++;
    }
    return count;
}

void print(std::vector<pair<int, int> > data)
{
    pair <int, int> temp;
    for (int i = 0; i < data.size(); ++i)
    {
        temp = data.at(i);
        printf("%d, %d\n", temp.first, temp.second);
    }
}

int main()
{
    int temp;
    pair<int, int> t_pair;
    n = scan_d();
    // init
    for(int i=0; i < 2*n; i++) {
        temp = scan_d();
        t_pair.first = temp;
        t_pair.second = i;
        v.push_back(t_pair);
        f.push_back(-1);
    }
    sort(v.begin(), v.end(), sort_f);
    // print(v);
    int i=0, c_1=0, c_2=0, c_1_d=0, c_2_d=0;
    while(i < 2*n)
    {
        temp = get_range(i);
        if(temp == 0) {
            if(c_1 > c_2) {
                f[v[i].second] = 2;
                c_2++;
                c_2_d++;
            }
            else {
                f[v[i].second] = 1;
                c_1++;
                c_1_d++;
            }
            i++;
        } else {
            f[v[i].second] = 1;
            i++;
            f[v[i].second] = 2;
            i = i + temp;
            c_1++;
            c_2++;
            c_1_d++;
            c_2_d++;
        }
    }
    i = 0;
    while(i < 2*n) {
        if(f[i] == -1) {
            if(c_1 < n) {
                f[i] = 1;
                c_1++;
            } else {
                f[i] = 2;
                c_2++;
            }
        }
        i++;
    }
    println_d(c_1_d*c_2_d);
    for(i=0; i< 2*n -1; i++) {
        printf("%d ", f[i]);
    }
    printf("%d\n", f[i]);
    return 0;
}