// Problem Set 401A
#include <iostream>
#include <cstdio>

using namespace std;


int main()
{
    int n, x, temp, sum;
    scanf("%d", &n);
    scanf("%d", &x);
    sum = 0;
    for(int i=0; i < n; i++)
    {
        cin >> temp;
        sum+=temp;
    }
    if (sum > 0)
        if (sum > x) {
            if ((sum%x) == 0) {
                printf("%d\n", sum/x);
            } else {
                printf("%d\n", sum/x + 1);
            }
        }
        else
            printf("1\n");
    else if (sum == 0)
        printf("0\n");
    else
    {
        sum = -sum;
        if (sum > x) {
            if ((sum%x) == 0) {
                printf("%d\n", sum/x);
            } else {
                printf("%d\n", sum/x + 1);
            }
        }
        else
            printf("1\n");

    }
    return 0;
}