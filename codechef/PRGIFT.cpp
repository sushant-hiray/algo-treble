// AUG14 LunchTime challenge
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int T, n, k, cur, temp;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> n >> k;
        cur = 0;
        for(int j = 0; j < n; j++) {
            cin >> temp;
            if ((temp % 2) == 0)
                cur++;
        }
        if ((k == 0) && (cur == n)) {
            std::cout<<"NO"<<std::endl;
        } else if (cur >= k) {
            std::cout<<"YES"<<std::endl;
        } else {
            std::cout<<"NO"<<std::endl;
        }
    }
    return 0;
}