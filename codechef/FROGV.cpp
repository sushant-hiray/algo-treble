// JUL14 Long Challenge

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#define ll long long
using namespace std;

inline int fastread(){
    int a=0;
    char c=getchar_unlocked();
    while(c<48 || c>57) c=getchar_unlocked();
    while(c>=48 && c<=57)
    {
        a=(a<<3)+(a<<1)+c-'0';
        c=getchar_unlocked();
    }
    return a;
}
void print(std::vector<pair<ll, ll> > data)
{
    pair <ll, ll> temp;
    for (ll i = 0; i < data.size(); ++i)
    {
        temp = data.at(i);
        printf("%lld, %lld\n", temp.first, temp.second);
    }
}

bool comp_f(pair<ll, ll> i, pair<ll, ll> j)
{
    return (i.first < j.first);
}

bool comp_s(pair<ll, ll> i, pair<ll, ll> j)
{
    return (i.second < j.second);
}

int main()
{
    ll n, k, p, data_i, f, s;
    scanf("%lld %lld %lld",&n, &k, &p);
    vector <pair<ll, ll> > data, up;
    pair <ll, ll> temp, temp2;

    for (ll i = 0; i < n; ++i)
    {
        scanf("%lld", &data_i);
        temp.first = data_i;
        temp.second = i;
        data.push_back(temp);
        up.push_back(temp);
    }

    sort(data.begin(), data.end(), comp_f);
    temp.second = data.at(n-1).second;
    temp.first = k + data.at(n-1).first;
    up[n-1] = temp;
    
    for(ll i=n-2; i >= 0; i--)
    {
        temp = data.at(i);
        temp2 = data.at(i+1);
        if ((temp2.first - temp.first) <= k)
            temp.first = up.at(i+1).first;
        up[i] = temp;
    }

    sort(up.begin(), up.end(), comp_s);

    for(ll i=0; i < p; i++)
    {
        scanf("%lld %lld", &f, &s);
        temp = up.at(f - 1);
        temp2 = up.at(s - 1);
        if (temp.first == temp2.first)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}