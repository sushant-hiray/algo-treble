#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

char mxor(char a, char b)
{
    if (a == '0' && b == '0')
        return '0';
    else if (a == '0' && b =='1')
        return '1';
    else if (a == '1' && b == '0')
        return '1';
    else if (a == '1' && b == '1')
        return '0';
    return '-1';
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, k;
    scanf("%d %d", &n, &k);
    char* s;
    s = new char[n+k];
    scanf("%s", s);
    char * f = new char[n+k];
    f[0] = s[0];
    for(int i=1; i <= k - 1; i++) {
        f[i] = mxor(s[i], s[i-1]);
        //cout << i << " " << f[i] << endl;
    }
    char temp;
    for(int i=k; i <=n-1; i++) {
        temp = mxor(s[i-1], s[i]);
        f[i] = mxor(temp, f[i-k]);
        //cout << i << " " << temp  << "  " << f[i] << endl;
    }
    f[n] = '\0';
    printf("%s\n", f);
    return 0;
}
