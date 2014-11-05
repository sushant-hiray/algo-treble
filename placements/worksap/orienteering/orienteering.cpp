#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <list>
#include <queue>
#include <cmath>
#define INT_MAX 1000000009
using namespace std;

struct edge;
struct checkpoint_edge;

struct location {
    int x;
    int y;
    location(int i=0, int j=0) {
        x = i;
        y = j;
    }
    void print() {
        cout << "[" << x << "," << y << "]";
    }

    bool eq(location l) {
        if ((x == l.x) && (y == l.y))
            return true;
        else return false;
    }
};


struct node {
    int id;
    int wt;
    int val;
    location l;
    bool visited;
    list<edge*> neighbors;
    node(int v, int i, int j) {
        l.x = i;
        l.y = j;
        val = v;
        visited = false;
        wt = INT_MAX;
    }
    void print() {
        cout << wt << " | ";
        l.print();
    }
    void reset() {
        visited = false;
        wt = INT_MAX;
    }

    bool eq(node n) {
        return l.eq(n.l);
    }
};

struct edge
{
    int weight;
    node* a;
    edge(node* _a, int wt) {
        a = _a;
        weight = wt;
    }
};


struct checkpoint_node
{
    int cp_id; 
    int node_id;
    int wt;
    bool visited;
    string nid_str;
    list<checkpoint_edge*> neighbors;
    checkpoint_node(int c,int n, int m, int w=INT_MAX) {
        cp_id = c;
        node_id = n;
        wt = w;
        visited = false;
        string str(m,'0');
        int i=m-1;
        while(i>=0) {
            str[i] = ((n & 1) ? '1' : '0');
            n = n >> 1;
            i--;
        }
        nid_str = str;
    }

    void reset() {
        visited = false;
        wt = INT_MAX;
    }

    bool eq(checkpoint_node n) {
        return (cp_id == n.cp_id && node_id == n.node_id);
    }

    void print() {
        cout << wt << " | " << cp_id << ": " << nid_str;
    }

    bool is_valid() {
        return (nid_str[cp_id]=='1' ? true : false);
    }
};

struct checkpoint_edge
{
    int weight;
    checkpoint_node* a;
    checkpoint_edge(checkpoint_node* _a, int wt) {
        a = _a;
        weight = wt;
    }
};

class node_comparison
{
public:
    
    bool operator() (const node* lhs, const node* rhs) const
    {
        return (lhs->wt > rhs->wt);
    }

    bool operator() (const checkpoint_node* lhs, const checkpoint_node* rhs) const
    {
        return (lhs->wt > rhs->wt);
    }
};

class Orienteering
{
private:
    vector<vector<node*> > maze;
    vector<vector<checkpoint_node*> > cp_nodes;
    vector<location> checkpoint;
    vector<vector<int> > weights;
    int width;
    int height;
    int cp_s;
    void parse_input();
    void print_index(int);
    void print_maze();
    void print_cp();
    void init_graph();
    void calc_weights();
    void generate_cp_graph();

    template<typename T>
    int shortest_path(T*, T* );
    
    template<typename T>  
    void reset_graph(vector<vector<T*>> &);
    
public:
    Orienteering();
    void main();
};


Orienteering::Orienteering()
{
    return;
}

void Orienteering::main()
{
    parse_input();
    init_graph();
    print_maze();
    calc_weights();
    generate_cp_graph();
    print_cp();
    
}

void Orienteering::parse_input()
{
    cin >>width>>height;
    for(int i=0;i<height;i++) {
        std::vector<node*> t;
        for (int j = 0; j < width; j++) {
            char ch;
            cin >> ch;
            switch(ch) {
                case '#' : {
                    node* n = new node(-1,i,j);
                    t.push_back(n);
                    break;
                } case '@' : {
                    node* n = new node(2,i,j);
                    checkpoint.push_back(location(i,j));
                    t.push_back(n);
                    break;
                } case '.' : {
                    node* n = new node(1,i,j);
                    t.push_back(n);
                    break;
                } case 'S' : {
                    node* n = new node(3,i,j);
                    t.push_back(n);
                    break;
                } case 'G' : {
                    node* n = new node(4,i,j);
                    t.push_back(n);
                    break;
                }
                default : {
                    node* n = new node(6,i,j);
                    t.push_back(n);
                    break;
                }
            }
        }
        maze.push_back(t);
    }

    cp_s = checkpoint.size();
    for(int i=0;i<cp_s;i++) {
        weights.push_back(vector<int>(cp_s, INT_MAX));
        vector<checkpoint_node*> temp;
        for(int j=0;j<pow(2, cp_s);j++) {
            checkpoint_node* cp_n = new checkpoint_node(i,j, cp_s);
            temp.push_back(cp_n);
        }
        cp_nodes.push_back(temp);
    }
}


void Orienteering::print_index(int i)
{
    switch(i) {
        case -1 : {
            cout<<'#';
            break;
        } case 2 : {
            cout<<'@';
            break;
        } case 1 : {
            cout<<'.';
            break;
        } case 3 : {
            cout<<'S';
            break;
        } case 4 : {
            cout<<'G';
            break;
        }
    }
}

void Orienteering::print_maze()
{
    for(int i=0;i<maze.size();i++) {
        for(int j=0;j<maze[i].size();j++) {
            cout << "{";
            maze[i][j]->print();
            cout << "--->";
            for(list<edge*>::iterator it = maze[i][j]->neighbors.begin(); it!= maze[i][j]->neighbors.end(); it++) {
                ((*it)->a)->print();
                cout << ", ";
            }
            cout << "}"<<endl;
        }
        cout << endl;
    }
}

void Orienteering::print_cp()
{
    for(int i=0;i<checkpoint.size();i++) {
        checkpoint[i].print();
        cout << " ";
    }
    cout << endl;
    for(int i=0;i<checkpoint.size();i++) {
        for(int j=0;j<checkpoint.size();j++) {
            cout << weights[i][j] << " ";
        }
    cout << endl;
    }


    for(int i=0;i<cp_nodes.size();i++) {
        for(int j=0;j<cp_nodes[i].size();j++) {
            cout << "{";
            cp_nodes[i][j]->print();
            cout << "--->";
            for(auto it = cp_nodes[i][j]->neighbors.begin(); it!= cp_nodes[i][j]->neighbors.end(); it++) {
                ((*it)->a)->print();
                cout << ", ";
            }
            cout << "}"<<endl;
        }
    }
}



void Orienteering::init_graph()
{
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            int addx = -1;
            int addy = -1;
            if (maze[i][j]->val!=-1) {
                for(;addx<=1;addx+=2) {
                    if ((i+addx>=0) && (i+addx<height) && maze[i+addx][j]->val!=-1) {
                            edge* e = new edge(maze[i+addx][j], 1);
                            (maze[i][j]->neighbors).push_back(e);
                    }
                }
                for(;addy<=1;addy+=2) {
                    if ((j+addy>=0) && (j+addy<width) && maze[i][j+addy]->val!=-1) {
                        edge* e = new edge(maze[i][j+addy], 1);
                        (maze[i][j]->neighbors).push_back(e);
                    }
                }
            }
        }
    }
}

void Orienteering::generate_cp_graph()
{
    for(int i=0; i<cp_s;i++) {
        for(int j=0; j < pow(2,cp_s);j++) {
            if (cp_nodes[i][j]->is_valid()) {
                string str = cp_nodes[i][j]->nid_str;
                for(int k=0;k <cp_s;k++) {
                    if (str[k]=='0' && i!=k) {
                        int new_id = j + pow(2, cp_s - 1 - k);
                        checkpoint_edge* e = new checkpoint_edge(cp_nodes[k][new_id], weights[i][k]);
                        (cp_nodes[i][j]->neighbors).push_back(e);
                    } 
                }
            }
        }
    }
}

template<typename T>
void Orienteering::reset_graph(vector<vector<T*>>& graph)
{
    for(int i=0;i<graph.size();i++) {
        for(int j=0;j<graph[i].size();j++) {
            graph[i][j]->reset();
        }
    }
}

template<typename T>
int Orienteering::shortest_path(T* cur, T* end) {
    cur->wt=0;
    priority_queue<T*, std::vector<T*>, node_comparison> pq;
    pq.push(cur);
    while(!pq.empty()) {
        cur = pq.top();
        cur->visited=true;
        if (cur->eq(*end)) {
            return cur->wt;
        } else {
            pq.pop();
            for(auto it = cur->neighbors.begin(); it!=cur->neighbors.end();it++) {
                if ((*it)->a->wt >  cur->wt + (*it)->weight) {
                    (*it)->a->wt = cur->wt+(*it)->weight;
                    pq.push((*it)->a);
                }
            }
        }
    }
    return INT_MAX;
}

void Orienteering::calc_weights()
{
    for(int i=0;i<checkpoint.size();i++) {
        for(int j=0;j<checkpoint.size();j++) {
            if (i==j)
                weights[i][j]=0;
            else if (j < i)
                weights[i][j] = weights[j][i];
            else {
                reset_graph<node>(maze);
                weights[i][j] = shortest_path<node>(maze[checkpoint[i].x][checkpoint[i].y], 
                                maze[checkpoint[j].x][checkpoint[j].y]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    Orienteering o;
    o.main();    
    return 0;
}