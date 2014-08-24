// Problem Set 382C
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long
using namespace std;

int main()
{
    int n,temp,i;
    cin>>n;
    vector<long int> vec;
    for(i=0;i<n;i++)
    {
        cin>>temp;
        vec.push_back(temp);
    }
    sort(vec.begin(), vec.end());
    if(n==1)
    {
        cout<<-1<<endl;
        return 0;
    }
    set<long int> diff;
    for(i=0;i<n-1;i++)
        diff.insert(vec[i+1]-vec[i]);

    if(diff.size() == 1)
    {
        // Only a single diff, complete AP
        int j=0;
        int d[1];
        for (std::set<long int>::iterator it=diff.begin(); it!=diff.end(); ++it)
            d[j++]=*it; 
        if(d[0]==0)
        {
            // Difference is 0, so only 1 new no can be added
            cout<<1<<endl<<vec[0]<<endl;
        }
        else if(n==2 && (vec[0]+vec[1])%2==0)
        {
            // Squeeze one number in between
            cout<<3<<endl;
            long int d = (vec[1]-vec[0]);
            cout<<vec[0]-d<<" "<<(vec[0]+vec[1])/2<<" "<<vec[1]+d<<endl;
        }
        else
        {
            cout<<2<<endl;
            long int d = (vec[1]-vec[0]);
            cout<<vec[0]-d<<" "<<vec[n-1]+d<<endl;
        }
    }
    else if(diff.size() == 2)
    {
        int j=0;
        int d[2];
        for (std::set<long int>::iterator it=diff.begin(); it!=diff.end(); ++it)
            d[j++]=*it; 
        
        sort(d,d+2);
        if(d[0]*2 == d[1])
        {   
            int c=0,an;
            for(j=0;j<n-1;j++)
            {
                if(vec[j+1]-vec[j] == d[1])
                {
                    an=vec[j]+d[0];
                    c++;
                }
            }
            if(c==1)
            {
                cout<<1<<endl<<an<<endl;
            }
            else
            {
                cout<<0<<endl;
            }
        }
        else
        {
            cout<<0<<endl;
        }
    }
    else
    {
        cout<<0<<endl;
    }
}