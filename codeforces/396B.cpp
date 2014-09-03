// 396A
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

bool isprime(ll n) {
	if((n % 2) == 0)
		return false;
	else {
		for(int i=3; i*i<=n; i=i+2)
			if(n%i == 0)
				return false;
		return true;
	}
}

ll gcd(ll a, ll b) {
	if(b == 0)
		return a;
	else {
		ll t;
		while(b != 0) {
			t = a;
			a = b;
			b = t%b;
		}
		return a;
	}
}


int main()
{
	ll t, n, u, v, k, nm, dn, g;
	cin>>t;
	while(t--) {
		cin>>n;
		if ((n%2) == 1) {
			u = n;
			v = n+2;
		}
		else {
			u = n-1;
			v = n+1;
		}	
		while(1) {
			if(isprime(u))
				break;
			else
				u = u-2;
		}
		while(1) {
			if(isprime(v))
				break;
			else
				v = v+2;
		}
		k = (v*u);
		nm = k - 2*v + 2*n - 2*u + 2;
		dn = 2*k;
		g = gcd(nm, dn);
		nm = nm/g;
		dn = dn/g;
		cout<<nm<<"/"<<dn<<endl;
	}
	return 0;
}