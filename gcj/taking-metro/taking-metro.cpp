#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <cmath>
#include <map>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;

struct index {
    int m_ind; // metro index
    int s_ind; // serial index
    index(int m, int s) {m_ind = m; s_ind = s;}
    index(){m_ind=-1;s_ind=-1;}
    void print() const { cout <<"["<<m_ind<<", "<<s_ind<<"]";}
};

struct duo
{
    index first;
    index second;
    int distance;
    duo(int a, int b, int c, int d, int e) {
        first.m_ind = a;
        first.s_ind = b;
        second.m_ind = c;
        second.s_ind = d;
        distance = e;
    }
    duo(index a, index b, int d) {
        first.m_ind = a.m_ind;
        first.s_ind = a.s_ind;
        second.m_ind = b.m_ind;
        second.s_ind = b.s_ind;
        distance = d;
    }
    void print() {
        cout << "DUO ";
        first.print();
        cout << " , ";
        second.print();
        cout << "cost is " << distance << endl;
    }
};

struct station
{
     bool should_wait; // while traversing, should this wait
     bool visited;
     index ind;
     int wait_time;
     ll cur_dist; // current distance
     list<station*> neighbors;
     station(int m, int s, int w) {
        ind.m_ind = m;
        ind.s_ind = s;
        should_wait = false;
        wait_time = w;
        cur_dist = pow(2,32) - 1;
        visited = false;
    }
    void print() {
        ind.print();
        cout << " " << cur_dist<<endl;
        
    }
    bool different (station* st) {
        if(ind.m_ind != (st->ind).m_ind)
            return true;
        else return false;
    }
};

int index_compare(const index& lhs, const index& rhs)
{
    if (lhs.m_ind < rhs.m_ind) return 1;
    else if ((lhs.m_ind == rhs.m_ind) && (lhs.s_ind < rhs.s_ind)) return 1;
    else if ((lhs.m_ind == rhs.m_ind) && (lhs.s_ind == rhs.s_ind)) return 0;
    else return -1;
}

struct pqcomp
{
    bool operator() (const station* lhs, const station* rhs) const {
        return lhs->cur_dist > rhs->cur_dist;
    }
};
bool classcomp(const duo& lhs, const duo& rhs)
{
    int a = index_compare(lhs.first, rhs.first);
    int b = index_compare(lhs.second, rhs.second);
    if(a==1) return true;
    else if (a==0 && b>=0) return true;
    else return false;
}

int find(vector<duo>& hash, index a, index b)
{
    duo f(a,b,0);
    bool check = false;
    int mini=-1;
    for(int i=0;i<hash.size();i++) {
        int l = index_compare(hash[i].first, f.first);
        int m = index_compare(hash[i].second, f.second);
        if (l==0 && m==0) {
            if (!check) {
                mini = hash[i].distance;
                check =true;
            }
            else {
                mini = min(mini, hash[i].distance);
            }
        } else if (check)
            return mini;
    }
    return mini;
}

void print(vector<duo>& hash)
{
    for(int i=0;i<hash.size();i++) {
        hash[i].print();
    }
    cout << "************************" << endl;
}
int djikstra(vector<vector<station*> >& v, vector<duo>& hash, int i1, int j1, int i2, int j2)
{
    priority_queue<station*, vector<station*>, pqcomp> q;
    v[i1][j1]->cur_dist=0;
    v[i1][j1]->should_wait=true;
    q.push(v[i1][j1]);
    bool check = false;
    while(!q.empty()) {
        station* top = q.top();
        if (index_compare((top)->ind, index(i2,j2)) == 0) {
            cout<<"FINALLY"<<endl;
            v[i2][j2]->print();
            check = true;
            break;
        }
        top->visited = true;
        q.pop();
        int cur = top->cur_dist;
        list<station*>::iterator it = (top->neighbors).begin();
        cout << "curr ";
        top->print();
        // cout << "cur is "<<cur<<endl;
        while(it!=(top->neighbors).end()) {
            if (!((*it)->visited)) {
                int dij = find(hash, top->ind,(*it)->ind);
                // cout << "found neighbor at " << dij<<endl;
                bool shift = top->different(*it);
                if (top->should_wait && !shift)
                        dij+=top->wait_time;
                dij +=cur;
                if (shift)
                    (*it)->should_wait = true;
                if ((*it)->cur_dist > dij) {
                    (*it)->cur_dist = dij;
                    q.push(*it);
                    cout << "neigh ";
                    (*it)->print();
                }
            }
            ++it;
        }
    }
    if (check) {
        return v[i2][j2]->cur_dist;
    }
    return -1;
}

void initialize(vector<vector<station*> >& v)
{
    for(int i=1; i<v.size();i++) {
        for(int j=1;j<v[i].size();j++) {
            v[i][j]->cur_dist = pow(2,32) - 1;
            v[i][j]->should_wait = false;
            v[i][j]->visited = false;
        }
    }
}

void print(vector<vector<station*> >& v)
{
    for(int i=1; i<v.size();i++) {
        for(int j=1;j<v[i].size();j++) {
            v[i][j]->print();
        }
    }
}

int main()
{
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        int N;
        cin >> N;
        vector<vector<station*> > metro;
        vector<station*> temp;
        metro.push_back(temp); //adjusting index
        vector<duo> dist;
        for(int n=1;n<=N;n++) {
            int sn, w;
            cin >> sn >> w;
            vector<station*> line;
            station* st = new station(n,0,0);
            line.push_back(st);

            for(int s=1;s<=sn;s++) {
                st = new station(n,s,w);
                line.push_back(st);
            }
            metro.push_back(line);

            for(int s=1;s<sn;s++) {
                int d;
                cin >> d;
                index first(n,s);
                index second(n,s+1);
                dist.push_back(duo(n,s,n,s+1,d));
                dist.push_back(duo(n,s+1,n,s,d));
                (metro[n][s])->neighbors.push_back(metro[n][s+1]);
                (metro[n][s+1])->neighbors.push_back(metro[n][s]);
            }
        }
        int M;
        cin >> M;
        for(int m=1;m<=M;m++) {
            int a,b,c,d,e;
            cin >> a>>b>>c>>d>>e;
            index first(a,b);
            index second(c,d);
            dist.push_back(duo(a,b,c,d,e));
            dist.push_back(duo(c,d,a,b,e));
            (metro[a][b])->neighbors.push_back(metro[c][d]);
            (metro[c][d])->neighbors.push_back(metro[a][b]);
        }
        int Q;
        cin >> Q;
        cout << "Case #"<<t<<":\n";
        sort(dist.begin(), dist.end(), classcomp);
        initialize(metro);
        // print(dist);
        // cout<<find(dist,index(10,1),index(2,1));
        for(int q=1;q<=Q;q++) {
            int a,b,c,d;
            cin >> a>>b>>c>>d;
            initialize(metro);
            int ans = djikstra(metro,dist,a,b,c,d);
            cout << ans << endl;
        }
        metro.clear();
        dist.clear();
        
    }
}