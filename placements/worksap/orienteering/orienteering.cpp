#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <list>
#include <queue>
#define INT_MAX 1000000009
using namespace std;

struct edge;

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



class node_comparison
{
public:
    bool operator() (const node* lhs, const node* rhs) const
    {
        return (lhs->wt < rhs->wt);
    }
};

class Orienteering
{
private:
    vector<vector<node*> > maze;
    vector<location> checkpoint;
    vector<vector<int> > weights;
    int width;
    int height;
    void parse_input();
    void print_index(int);
    void print_maze();
    void print_cp();
    void init_graph();
    void reset_graph();
    void calc_weights();
    int shortest_path(location a, location b);
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
    print_cp();
    cout << shortest_path(location(2,1), location(2,3)) << endl;
    
}

void Orienteering::parse_input()
{
    cin >>width>>height;
    for(int i=0;i<height;i++) {
        std::vector<node*> t;
        for (int j = 0; j < width; j++) {
            char ch;
            cin >> ch;
            cout << ch;
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
        cout << endl;
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

void Orienteering::reset_graph()
{
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            maze[i][j]->reset();
        }
    }
}


int Orienteering::shortest_path(location a, location b) {
    node * end = maze[b.x][b.y];
    node * cur = maze[a.x][a.y];
    cur->wt=0;
    priority_queue<node*, std::vector<node*>, node_comparison> pq;
    pq.push(cur);
    while(!pq.empty()) {
        cur = pq.top();
        cur->visited=true;
        if (cur->eq(*end)) {
            return cur->val;
        } else {
            pq.pop();
            for(list<edge*>::iterator it = cur->neighbors.begin(); it!=cur->neighbors.end();it++) {
                if ((*it)->a->wt >  cur->wt + 1) {
                    (*it)->a->wt = cur->wt+1;
                    pq.push((*it)->a);
                }
            }
        }
    }
    return INT_MAX;
}


int main(int argc, char const *argv[])
{
    Orienteering o;
    o.main();    
    return 0;
}