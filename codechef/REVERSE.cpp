// AUG14 LunchTime challenge
#include <iostream>
#include <cstdio>
#include <stdlib.h> 
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

class ComparePair {
    public:
    bool operator()(pair<int, int> t1, pair<int, int> t2) // Returns true if t1 is earlier than t2
    {
       if (t1.first > t2.first) return true;
       return false;
    }

};

map<int, list<int> > emap, emap_r;

list<int> find(map<int, list<int> >& emap, int key)
{
    std::map<int, list<int> >::iterator it = emap.find(key);
    std::list<int> first;
    if (it!=emap.end())
        return it->second;
    else
        return first;
}

void print(std::vector<int> v)
{
    cout <<"[";
    for(int i=1; i< v.size();i++)
        cout << v.at(i) << ", ";
    cout << "]\n";
}


int main()
{
    int nv, ne, v1, v2;
    std::map<int, list<int> >::iterator it = emap.end();
    std::map<int, list<int> >::iterator it_r = emap_r.end();

    cin >> nv >> ne;    
    std::vector<int> data (nv + 1);
    std::vector<bool> visited (nv + 1);

    std::priority_queue<pair<int, int>, vector<pair<int, int> >, ComparePair> q;

    //Initialization
    for(int i = 0; i < nv; i++)
    {
        data.at(i +1) = 100000;
        visited.at(i+1) = false;
    }

    // Reading Input
    for (int i = 0; i < ne; i++)
    {
        cin >> v1 >> v2;
        it = emap.find(v1);
        it_r = emap_r.find(v2);
        if (it == emap.end()) {
            std::list<int> mylist;
            mylist.push_back(v2);
            emap.insert(std::pair<int,std::list<int> >(v1, mylist));
        } else {
            (it->second).push_back(v2);
        }
        if (it_r == emap_r.end()) {
            std::list<int> mylist;
            mylist.push_back(v1);
            emap_r.insert(std::pair<int,std::list<int> >(v2, mylist));
        } else {
           (it_r->second).push_back(v1); 
        }
    }

    data.at(1) = 0;
    q.push(pair<int, int>(0, 1));
    int min_val;
    bool found = false;

    while (!q.empty())
    {
        std::pair<int, int> top = q.top();
        //top->second is the id of the vertex
        int locm = top.second;
        int cur = top.first;
        if (locm == nv) {
            found = true;
            std::cout << top.first << std::endl;
            break;
        }

        list<int> a (find(emap, locm));
        list<int> b (find(emap_r, locm));
        visited.at(locm) = true;
        q.pop();
        for(list<int>::iterator it = a.begin(); it!= a.end(); ++it)
        {
            if(!visited.at(*it)) {
                min_val = min(data.at(*it), cur);
                data.at(*it) = min_val;
                q.push(pair<int, int>(min_val, *it));
            }
        }

        for(list<int>::iterator it = b.begin(); it!= b.end(); ++it)
        {
            if(!visited.at(*it)) {
                min_val = min(data.at(*it), 1 + cur);
                data.at(*it) = min_val;
                q.push(pair<int, int>(min_val, *it));
            }
        }

    }
    if (!found) 
        std::cout <<"-1"<<std::endl;
    return 0;
}