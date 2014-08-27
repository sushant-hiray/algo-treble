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

struct node{
  int value; // index
  char id;   // 'H' or 'V'
  node* left = NULL;
  node* right = NULL;
};

struct tree{
    node* head = NULL;
};

int cur = 0;

void build(node* head, int h, int v)
{
    if (h > 0) {
        node* left = new node;
        left->id = 'H';
        head->left = left;
        build(head->left, h - 1, v);
    }
    if (v > 0) {
        node* right = new node;
        right->id = 'R';
        head->right = right;
        build(head->right, h, v - 1);
        head->right->id = 'V';
    }
    return;
}

void init(node* head)
{
    if ((head->left == NULL) && (head->right == NULL)) {
        head->value = cur;
        cur++;
    }
    else if (head->left == NULL) {
        init(head->right);
        head->value = head->right->value;
    } else if (head->right == NULL) {
        init(head->left);
        head->value = head->left->value;
    } else {
        init(head->left);
        init(head->right);
        head->value = head->right->value;
    }
    return;
}

void find(node* head, int count)
{
    if (head == NULL)
        return;
    else if ((head->left!= NULL) && (count <= head->left->value)) {
        if (head->id!= 'P')
            cout << head->id;
        find(head->left, count);
        return;
    } else if ((head->right!= NULL) && (count <= head->right->value)) {
        if (head->id!= 'P')
            cout << head->id;
        find(head->right, count);
        return;
    } else {
        if (head->id!= 'P')
            cout << head->id;
        return;
    }
}

void print(node* head, int count)
{
    if (head == NULL)
        return;
    else {
        for(int i=0; i < count; i++) {
            cout << "-";
        }
        cout<< " "<<head->value << head->id << endl;
        print(head->left, count+1);
        print(head->right, count+1);
        return;
    }
}

void my_delete(node* head)
{
    if (head == NULL)
        return;
    else {
        my_delete(head->left);
        my_delete(head->right);
        delete head;
        return;
    }
}

int main()
{
    int t, n, m, k;
    t = scan_d();
    while(t!=0) {
        n = scan_d();
        m = scan_d();
        k = scan_d();
        node* head = new node;
        head->left = NULL;
        head->right = NULL;
        head->id = 'P';
        cur = 0;
        build(head, n, m);
        init(head);
        find(head, k);
        cout << endl;
        my_delete(head);
        t--;
    }
    return 0;
}
