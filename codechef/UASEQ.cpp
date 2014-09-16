// SEPT14 UASEQ
// Basic idea is that, given the fact that n is very less. i and j are such that all numbers before i will need to be changed
// and all numbers after j will need to be changed. k*k ways of choosing them. Each choice will need the whole traversal.
// Therefore order n*k*k
#include <cassert>
#include <cstdio>
#include <algorithm>
#define lld long long
using namespace std;


int main()
{
	int n, k, i, j, a[100000 + 5], remain, diff, a0, t, count;
	// input
	scanf("%d %d", &n, &k);
	for(i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	pair<lld, lld> ret = make_pair(2000000000, 2000000000);
	for(i = 1; i <= k+1; i++) {
		for(j = n + i - k - 1; j <= n; j++) {
			if ((a[j] - a[i]) % (j - i) != 0) continue;
			diff = (a[j] - a[i]) / (j - i);
			a0 = a[i] - diff * (i - 1);
			count = 0;
			for(t = 1; t <= n; t++) if (a[t] != a0 + (t - 1) * 1LL * diff) ++count;
			if (count <= k) ret = min(ret, make_pair(1LL * a0, 1LL * diff));
		}
	}
	for(i = 0; i < n; i++) printf("%lld ", ret.first + ret.second * 1LL * i);
	printf("\n");
    return 0;
}
