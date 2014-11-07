#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <list>
#include <stack>
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

vector<vector<int> > hamiltonian_length;

struct node {
    int id;
    int wt;
    int val;
    int cp_id;
    location l;
    node(int v, int i, int j, int cp, int d) {
        l.x = i;
        l.y = j;
        val = v;
        wt = INT_MAX;
        cp_id = cp;
        id = d;
    }
    void print() {
        cout << wt << " | ";
        l.print();
    }
    void reset() {
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
    string nid_str;
    
    checkpoint_node(int c,int n, int m, int w=INT_MAX) {
        cp_id = c;
        node_id = n;
        wt = w;
        string str(m,'0');
        int i=m-1;
        while(i>=0) {
            str[i] = ((n & 1) ? '1' : '0');
            n = n >> 1;
            i--;
        }
        nid_str = str;
    }

    checkpoint_node() {
        cp_id = -1;
        node_id = -1;
        wt = INT_MAX;
    }

    void reset() {
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
    bool operator() (const location& lhs, const location& rhs) const
    {
        return ((hamiltonian_length[lhs.x][lhs.y]) > (hamiltonian_length[rhs.x][rhs.y]));
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
    int cp_s;
    location start;
    location end;

    checkpoint_node* st_node;
    checkpoint_node* end_node;


    void parse_input();
    void print_index(int);
    void print_maze();
    void print_cp();
    void print_cp_weights();
    void init_graph();
    void calc_weights();
    void generate_cp_graph();
    int find_min();
    void dfs(node*);


    template<typename T>
    int shortest_path(T*, T* );
    int shortest_cp_path(checkpoint_node*, checkpoint_node* );
    template<typename T>  
    void reset_graph(vector<vector<T*>> &);
    
public:
    Orienteering();
    void main();
};


Orienteering::Orienteering()
{
    st_node = new checkpoint_node();
    end_node = new checkpoint_node();
    return;
}

void Orienteering::main()
{
    parse_input();
    // init_graph();
    // // print_maze();
    calc_weights();
    // print_cp();
    // print_cp_weights();
    
    // // print_cp();
    cout << "ANS is " << find_min() <<endl;
    
}

void Orienteering::parse_input()
{
    cin >>width>>height;

    int count = 0;
    for(int i=0;i<height;i++) {
        std::vector<node*> t;
        string str;
        cin >> str;
        for (int j = 0; j < width; j++) {
            char ch = str[j];
            switch(ch) {
                case '#' : {
                    node* n = new node(-1,i,j,-1,i*width+j);
                    t.push_back(n);
                    break;
                } case '@' : {
                    node* n = new node(2,i,j,count,i*width+j);
                    checkpoint.push_back(location(i,j));
                    t.push_back(n);
                    count++;
                    break;
                } case '.' : {
                    node* n = new node(1,i,j,-1,i*width+j);
                    t.push_back(n);
                    break;
                } case 'S' : {
                    node* n = new node(3,i,j,-1,i*width+j);
                    start = n->l;
                    t.push_back(n);
                    break;
                } case 'G' : {
                    node* n = new node(4,i,j,-1,i*width+j);
                    end = n->l;
                    t.push_back(n);
                    break;
                }
                default : {
                    node* n = new node(6,i,j,-1,i*width+j);
                    t.push_back(n);
                    break;
                }
            }
        }
        maze.push_back(t);
    }
    checkpoint.push_back(start);
    checkpoint.push_back(end);

    cp_s = checkpoint.size();
    
    maze[start.x][start.y]->cp_id = cp_s-2;
    maze[end.x][end.y]->cp_id = cp_s-1;
    weights.resize(cp_s , vector<int>( cp_s , INT_MAX ));
    hamiltonian_length.resize(cp_s, (vector<int>(pow(2,cp_s-2),INT_MAX)));
    
    // for(int i=0;i<cp_s;i++) {
    //     vector<checkpoint_node*> temp;
    //     for(int j=0;j<pow(2, cp_s-2);j++) {
    //         checkpoint_node* cp_n = new checkpoint_node(i,j,cp_s-2);
    //         temp.push_back(cp_n);
    //     }
    //     cp_nodes.push_back(temp);
    // }
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
            // for(list<edge*>::iterator it = maze[i][j]->neighbors.begin(); it!= maze[i][j]->neighbors.end(); it++) {
            //     ((*it)->a)->print();
            //     cout << ", ";
            // }
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
    for(int j=0;j<cp_s;j++) {
        cout << weights[0][j] << " ";
    }
    cout << endl;
    // st_node->print();
    // cout << "--->";
    // for(auto it = st_node->neighbors.begin(); it!=st_node->neighbors.end();it++) {
    //     cout << "<" << (*it)->weight << "> ";
    //     ((*it)->a)->print();
    //     cout << ", ";
    // }
    // cout << "}"<<endl;
    // for(int i=0;i<cp_s-2;i++) {
    //     for(int j=0;j<cp_nodes[i].size();j++) {
    //         cout << "{";
    //         cp_nodes[i][j]->print();
    //         cout << "--->";
    //         for(auto it = cp_nodes[i][j]->neighbors.begin(); it!= cp_nodes[i][j]->neighbors.end(); it++) {
    //             cout << "<" << (*it)->weight << "> ";
    //             ((*it)->a)->print();
    //             cout << ", ";
    //         }
    //         cout << "}"<<endl;
    //     }
    // }
}

void Orienteering::print_cp_weights()
{
    for(int i=0;i<cp_s;i++) {
        for(int j=0;j<cp_s;j++) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }

    // for(int i=0;i<cp_s;i++) {
    //     for(int j=0;j<height*width;j++) {
    //         cout << dfs_wt[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}

void Orienteering::init_graph()
{
    // for(int i=0;i<height;i++) {
    //     for(int j=0;j<width;j++) {
    //         int addx = -1;
    //         int addy = -1;
    //         if (maze[i][j]->val!=-1) {
    //             for(;addx<=1;addx+=2) {
    //                 if ((i+addx>=0) && (i+addx<height) && maze[i+addx][j]->val!=-1) {
    //                         edge* e = new edge(maze[i+addx][j], 1);
    //                         (maze[i][j]->neighbors).push_back(e);
    //                 }
    //             }
    //             for(;addy<=1;addy+=2) {
    //                 if ((j+addy>=0) && (j+addy<width) && maze[i][j+addy]->val!=-1) {
    //                     edge* e = new edge(maze[i][j+addy], 1);
    //                     (maze[i][j]->neighbors).push_back(e);
    //                 }
    //             }
    //         }
    //     }
    // }
}

int Orienteering::shortest_cp_path(checkpoint_node* start, checkpoint_node* end) {
    priority_queue<location, std::vector<location>, node_comparison> pq;
    int cp_s_left = cp_s - 2;
    int max_pow = pow(2, cp_s_left)-1;
    for(int i=0; i<cp_s_left;i++) {
        int new_id = pow(2, cp_s_left-i-1);
        hamiltonian_length[i][new_id] = weights[i][cp_s_left];
        pq.push(location(i,new_id));
    }
    location cur;
    location final(cp_s_left+1, max_pow);
    while(!pq.empty()) {
        cur = pq.top();
        if (cur.eq(final)) {
            return hamiltonian_length[cur.x][cur.y];
        } else {
            pq.pop();
            int i = cur.x;
            int j = cur.y;
            int n = j;
            int wt;
            string str(cp_s_left,'0');
            int q=cp_s_left-1;
            while(q>=0) {
                str[q] = ((n & 1) ? '1' : '0');
                n = n >> 1;
                q--;
            }
            for(int k=0;k <cp_s_left;k++) {
                if (str[k]=='0' && i!=k) {
                    int new_id = j + pow(2, cp_s_left - 1 - k);
                    wt = weights[i][k];
                    wt+=hamiltonian_length[cur.x][cur.y];
                    if (hamiltonian_length[k][new_id] > wt) {
                        hamiltonian_length[k][new_id] = wt;
                        pq.push(location(k,new_id));
                    }
                } 
            }
            if (j==max_pow) {
                wt =  weights[i][cp_s_left+1];
                wt+=  hamiltonian_length[cur.x][cur.y];
                if (hamiltonian_length[cp_s_left+1][max_pow] > wt) {
                    hamiltonian_length[cp_s_left+1][max_pow] = wt;
                    pq.push(final);
                }
            }
        }
    }
    return INT_MAX;


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
    priority_queue<T*, std::vector<T*>, node_comparison> pq;
    pq.push(cur);
    while(!pq.empty()) {
        cur = pq.top();
        if (cur->eq(*end)) {
            return cur->wt;
        } else {
            pq.pop();
            int i = cur->l.x;
            int j = cur->l.y;

            for(int k=j-1;k<=j+1;k+=2) {
                if(k>=0 && k<width && maze[i][k]->val<=4 && maze[i][k]->val>=1) {
                    if (maze[i][k]->wt > cur->wt + 1) {
                        maze[i][k]->wt = cur->wt + 1;
                        pq.push(maze[i][k]);
                    }
                }
            }

            for(int k=i-1;k<=i+1;k+=2) {
                if(k>=0 && k<height && maze[k][j]->val<=4 && maze[k][j]->val>=1) {
                    if (maze[k][j]->wt > cur->wt + 1) {
                        maze[k][j]->wt = cur->wt + 1;
                        pq.push(maze[k][j]);
                    }
                }
            }
        }
    }
    return INT_MAX;
}


void Orienteering::dfs(node* cur)
{
    cur->wt=0;
    int count = 0;
    priority_queue<node*, std::vector<node*>, node_comparison> pq;
    pq.push(cur);
    int cp_index = cur->cp_id;
    while(!pq.empty()) {
        cur = pq.top();
        if (cur->val==2 || cur->val==3 || cur->val==4) {
            weights[cp_index][cur->cp_id] = cur->wt;
            count++;
        } 
        if (count == cp_s)
            break;
        pq.pop();
        int i = cur->l.x;
        int j = cur->l.y;

        for(int k=j-1;k<=j+1;k+=2) {
            if(k>=0 && k<width && maze[i][k]->val<=4 && maze[i][k]->val>=1) {
                if (maze[i][k]->wt > cur->wt + 1) {
                    maze[i][k]->wt = cur->wt + 1;
                    pq.push(maze[i][k]);
                }
            }
        }

        for(int k=i-1;k<=i+1;k+=2) {
            if(k>=0 && k<height && maze[k][j]->val<=4 && maze[k][j]->val>=1) {
                if (maze[k][j]->wt > cur->wt + 1) {
                    maze[k][j]->wt = cur->wt + 1;
                    pq.push(maze[k][j]);
                }
            }
        }
    }
}

void Orienteering::calc_weights()
{
    for(int i=0; i<checkpoint.size();i++) {
        reset_graph<node>(maze);
        dfs(maze[checkpoint[i].x][checkpoint[i].y]);
    }
}

int Orienteering::find_min()
{
    int min_length;
    if (cp_s == 0) {
        reset_graph<node>(maze);
        maze[start.x][start.y]->wt=0;
        min_length = shortest_path<node>(maze[start.x][start.y], maze[end.x][end.y]);
        return min_length;
    } else if (cp_s == 1) {
        reset_graph<node>(maze);
        maze[start.x][start.y]->wt=0;
        min_length = shortest_path<node>(maze[start.x][start.y], maze[checkpoint[0].x][checkpoint[0].y]);

        reset_graph<node>(maze);
        maze[checkpoint[0].x][checkpoint[0].y]->wt=0;
        min_length += shortest_path<node>(maze[checkpoint[0].x][checkpoint[0].y],  maze[end.x][end.y]);
        return min_length;
    } else {
        st_node->wt = 0;
        min_length = shortest_cp_path(st_node, end_node);
        return min_length;
    }
}

int main(int argc, char const *argv[])
{
    Orienteering o;
    o.main();    
    return 0;
}