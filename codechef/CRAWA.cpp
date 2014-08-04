// AUG14 LunchTime challenge

// Inferences: Focus only X-coord: odd numbers +ve, even numbers -ve stays in the same x at n = 2x, 2x + 1 
// corner case: 0 in above case strictly for n > 2: (n - 2)/4 ((n - 2)%4)->1,2 +ve or else negative
// y - coord: +- even numbers
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

bool is_valid_x(long long x)
{
    if ((x > 0) && ((x % 2) == 1))
        return true;
    else if ((x < 0) && ((x % 2) == 0))
        return true;
    else
        return false;
}

bool is_valid_y(long long y)
{
    if ((y % 2) == 0)
        return true;
    else
        return false;
}

bool is_in_range(long long high, long long low, long long n)
{
    if ((n >= low) && (n <= high))
        return true;
    else if ((n >= high) && (n <= low))
        return true;
    else
        return false;
}

long long get_n_x(long long x)
{
    if (x > 0) return 2*x;
    else return 2*(-x);
}

long long get_n_y(long long y)
{
    if (y > 0) return (2*y - 1);
    else return (2*(-y) + 1);
}

long long get_y_n(long long n)
{
    switch(n % 4) {
        case 1:
            return (n - 1)/(-2);
        case 2:
            return (n - 2)/(-2);
        case 3:
            return (n + 1)/2;
        case 0:
            return n/2;
    }
}

long long get_x_n(long long n)
{
    switch(n % 4) {
        case 1:
            return (n - 1)/(-2);
        case 2:
            return n / 2;
        case 3:
            return (n - 1)/2;
        case 0:
            return -n/2;
    }
}

bool in_range_y(long long y, long long x)
{
    //Assumes y is valid
    long long n, low, high;
    n = get_n_y(y);
    low = get_x_n(n);
    high = get_x_n(n + 1);
    return is_in_range(high, low, x);
}

bool in_range_x(long long x, long long y)
{
    //Assumes x is valid
    long long n, low, high;
    n = get_n_x(x);
    low = get_y_n(n);
    high = get_y_n(n + 1);
    return is_in_range(high, low, y);
}

int main()
{
    long long T, x, y, low, high, n_low;
    cin >> T;
    for (long long i=0; i < T; i++)
    {
        cin >> x >> y;
        if (is_valid_x(x)) {
            if (in_range_x(x, y)) 
                std::cout << "YES" << std::endl;
            else if(is_valid_y(y))
                std::cout << "YES" << std::endl;
            else
                std::cout << "NO" << std::endl;
        } else if (is_valid_y(y)) {
            if (in_range_y(y, x))
                std::cout << "YES" << std::endl;
            else if(is_valid_x(x))
                std::cout << "YES" << std::endl;
            else
                std::cout << "NO" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}
