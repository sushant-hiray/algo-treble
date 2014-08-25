// 427B
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    int n, t, c, temp;
    scanf("%d %d %d\n", &n, &t, &c);
    int l = 0, count = 0; 
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        if (temp > t) {
            if (l >= c)
                count = count + l - c + 1;
            l = 0;
        }
        else
            l++;
    }
    if (l >= c)
        count = count + l - c + 1;
    printf("%d\n", count);
    return 0;
}