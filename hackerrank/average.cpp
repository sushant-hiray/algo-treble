#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    
    while(t--)
    {
        int n, sum = 0, temp, count=0;
        int average;
        cin >> n;
        temp = 0;
        vector<int> i(n);
        for(temp = 0; temp < n; temp++)
        {
            cin >>i[temp];
            sum+=i[temp];
        }
        average = sum / n;
        average++;
        for(temp =0; temp < n; temp++)
        {
            if (i[temp] >= average)
                count++;
        }
        cout << count << endl;
    }
    return 0;
}
