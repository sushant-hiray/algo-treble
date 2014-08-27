// w-8 counter-game
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
using namespace std;

// finds the msb
unsigned long long msb(unsigned long long n) {
    for(int i = 63; i >= 0; i--) {
        if((n & (1ll<<i)) != 0)
            return 1ll << i;
    }
    return 0;
}

bool who_wins(unsigned long long n, int counter) {
    if(n == 1)
        return false;
    unsigned long long nextStep = ((n&(n-1)) == 0 ? n>>1 : n-msb(n));
    // !who_wins will make sure that we do not need to handle counters
    return who_wins(nextStep, counter++);
}


int main()
{
    unsigned long long num;

    int test;
    cin >> test;
    while(test--) {
        cin >> num;
        cout << (who_wins(num)?"Louise": "Richard");
        cout << "\n";
    }


