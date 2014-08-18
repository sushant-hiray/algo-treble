// JUL14 LunchTime challenge

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define ll long long

ll get_count(ll n)
{
    return ((n + 1)*n/2);
}

int main()
{
    ll t, n, cur;
    cin >> t;

    ll count;
    
    for(ll i=0; i < t; i++)
    {
        cin >> n;
        count = 0;
        getchar();
        for (ll j=0; j < n; j++)
        {
            cur = getchar();
            if (cur == '1') {
                count++;
            }
        }
        cout << count*(count + 1)/2 << endl;
    }
    return 0;

}