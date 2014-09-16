#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

int search(char c, map<char, int> m)
{
    for(char s = c+1; s<='z'; s++)
    {
        map<char, int>::iterator it = m.find(s);
        if (it!=m.end())
            return it->second;
    }
    return -1;
}

void swap(char* s, int i, int j)
{
    char a = s[i];
    s[i] = s[j];
    s[j] = a;
    
    int size = strlen(s);
    
    for(int k=0; k< (size-i-1)/2; k++){
		char temp = s[size - 1- k]; 
		s[size - 1 - k] = s[i+1+k];
		s[i+1+k] = temp;
	}
    return;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t;
    while(t--)
    {
        char* s;
        s = new char[105];
        scanf("%s\n", s);
        map<char, int> m;
        int find;
        bool c=false;
        for(int i= strlen(s) -1;i>=0;i--)
        {
            find = search(s[i], m);
            if (find!=-1) {
                swap(s, i, find);
                printf("%s\n", s);
                c=true;
                break;
            }
                pair<char, int> p;
                p.first = s[i];
                p.second = i;
                m.insert(p);
        }
        if(!c)
            printf("no answer\n");
    }
    return 0;
}
