// JULY14 Challenge
#include <iostream>
#include <cstdio>
#include <cmath>

#define ll long long

using namespace std;

ll get_steps(ll x, ll y)
{
    // assumed either x or y are zero
    return ( (x & 1) ? (2*x + 1) : 2*x) + ( (y & 1) ? (2*y - 1) : 2*y);
}

int main()
{
    int t;
    ll x, y, z, ans;
    cin >> t;
    for (int i=0; i < t; i++)
    {
        cin >> x >> y;
        x = abs(x);
        y = abs(y);
        z = min(x, y);
        ans = 2*z + get_steps(abs(x - z), abs(y - z));
        cout << ans << endl;
    }

}