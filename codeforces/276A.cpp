// 276A
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;

int main()
{
	ll n, k, f, t, max, temp;
	cin >> n >> k;
	max = 0;
	for(ll i=0; i < n; i++)
	{
		cin >> f >> t;
		if (t > k)
			temp = f - t - k;
		else
			temp = f;
		if (temp > max)
			max = temp;
	}
	cout << max << endl;
	return 0;
}