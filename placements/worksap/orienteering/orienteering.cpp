/**
 * @file orienteering.cpp  Orienteering class
 *
 * Project Clearwater - IMS in the Cloud
 * Author:  Sushant Hiray <http://sushant-hiray.me>
 *
 * The author can be reached by email at hiraysushant@gmail.com
 */

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

/**
 * struct: location
 * x: stores the first co-ordinate for referencing 2D vector
 * y: stores the second co-ordinate for referencing 2D vector
 */
struct location {
    int x;
    int y;
    // Default Constructor
    location(int i=0, int j=0) {
        x = i;
        y = j;
    }
    // Pretty print
    void print() {
        cout << "[" << x << "," << y << "]";
    }
    // Equality check
    bool eq(location l) {
        if ((x == l.x) && (y == l.y))
            return true;
        else return false;
    }
};

// Global vector used to store distances between any 2 checkpoints
vector<vector<int> > hamiltonian_length; 

/**
 * struct: node
 * id: unique id of the node, in the original maze
 * wt: weight of the node. Used during DFS
 * val: identifier to determine its type: start, end, checkpoint, deadend
 * cp_id: if it is a checkpoint, then unique checkpoint id, else -1
 * l: location in the original maze
 */

struct node {
    int id;
    int wt;
    int val;
    int cp_id;
    location l;
    // Constructor
    node(int v, int i, int j, int cp, int d) {
        l.x = i;
        l.y = j;
        val = v;
        wt = INT_MAX;
        cp_id = cp;
        id = d;
    }
    // Pretty print
    void print() {
        cout << wt << " | ";
        l.print();
    }
    // Reset the weight of the node
    void reset() {
        wt = INT_MAX;
    }
    // equality checking
    bool eq(node n) {
        return l.eq(n.l);
    }
};

/**
 * struct: checkpoint_node
 * cp_id: id of the checkpoint, references node_id in the original maze
 * node_id: unique id amongst checkpoint with with equal cp_id
 * nid_str: representation of node_id in bitstring
 */

struct checkpoint_node
{
    int cp_id; 
    int node_id;
    int wt;
    string nid_str;
    
    // constructor
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

    // default constructor
    checkpoint_node() {
        cp_id = -1;
        node_id = -1;
        wt = INT_MAX;
    }

    // reset nodes during dfs
    void reset() {
        wt = INT_MAX;
    }

    // equality check operator
    bool eq(checkpoint_node n) {
        return (cp_id == n.cp_id && node_id == n.node_id);
    }

    // pretty print
    void print() {
        cout << wt << " | " << cp_id << ": " << nid_str;
    }
};

/**
 * class: node_comparison
 * comparator operators for all the structs
 */

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

/**
 * class: Orienteering
 * Contains utility function to parse a maze and generate shortest path
 * 
 */


class Orienteering
{
private:
    vector<vector<node*> > maze; // the original maze generated via user input
    vector<location> checkpoint; // vector stogin locations of checkpoints in maze
    vector<vector<int> > weights; // stores the shortest path cost between 
                                  // every pair of checkpoints
    int width; // width of the maze
    int height; // height of the maze
    int cp_s; // total number of checkpoints (including start and end node)
    location start; // location of the start node
    location end; // location of the end node


    checkpoint_node* st_node; // starting point of traversal
    checkpoint_node* end_node; // end point of traversal


    // util function to parse the user input and initialize maze and 
    // checkpoint vectors
    void parse_input();
    
    // decodes parameter to user encoding and prints it
    // eg: -1 prints '#'; 2 prints '@' 
    void print_index(int);

    // decode the vector maze and print it
    void print_maze();

    // prints the location of the checkpoints
    void print_cp();

    // prints the weight matrix
    // cost of path for every pair of checkpoints
    void print_cp_weights();

    // calculates the weight matrix
    void calc_weights();

    // finds the shortest path from start node to end node
    // abiding the constraints that every checkpoint should be
    // visited atleast once
    int find_min();

    // generates graph dynamically till it visits all the checkpoint 
    // nodes
    // finds the shortest path with all the nodes from the parameter.
    void dfs(node*);

    // templatised version of shortest path.
    // It finds the shortest path if graph is already generated
    // find the shortest path from start node to end node
    template<typename T>
    int shortest_path(T* start, T* end);

    // finds the shortest path from start to end
    // It finds the shortest path by dynamically adding new nodes
    // i.e without explicilty generating the graph
    // This function has a huge improvement over shortest_path
    // function as it doesnot carry the overhead of generating
    // the entire graph
    int shortest_cp_path(checkpoint_node*, checkpoint_node* );

    // resets the entire graph
    // templatized version allows to reset graph with any type of nodes
    template<typename T>  
    void reset_graph(vector<vector<T*>> &);
    
public:
    // default constructor
    Orienteering();

    // main function: calls the relevant functions to find the shortest path
    void main();
};


Orienteering::Orienteering()
{
    // Initialising the private nodes
    st_node = new checkpoint_node();
    end_node = new checkpoint_node();
    return;
}

void Orienteering::main()
{
    parse_input();
    calc_weights();
    cout << find_min() <<endl;  
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
}

void Orienteering::print_cp_weights()
{
    for(int i=0;i<cp_s;i++) {
        for(int j=0;j<cp_s;j++) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }
}

int Orienteering::shortest_cp_path(checkpoint_node* start, checkpoint_node* end) {
    queue<location> pq;
    int cp_s_left = cp_s - 2;
    int max_pow = (1<<(cp_s_left))-1;


    for(int i=0; i<cp_s_left;i++) {
        int new_id = pow(2, i);
        hamiltonian_length[i][new_id] = weights[i][cp_s_left];
        pq.push(location(i,new_id));
    }



    location cur;
    location final(cp_s_left+1, max_pow);


    while(!pq.empty()) {
        cur = pq.front();
        if (cur.eq(final)) {
            return hamiltonian_length[cur.x][cur.y];
        } else {
            pq.pop();
            int i = cur.x;
            int j = cur.y;
            int wt;
            
            int str = j;
            
            for(char k=0;k <cp_s_left;k++) {
                if (!(str&1) && i!=k) {
                    int new_id = j | (1<<(k));
                    wt = weights[i][k];
                    wt+=hamiltonian_length[cur.x][cur.y];
                    if (hamiltonian_length[k][new_id] > wt) {
                        hamiltonian_length[k][new_id] = wt;
                        pq.push(location(k,new_id));
                    }
                }
                str = str >> 1;
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
    int cp_s_left = cp_s-2;
    if (cp_s_left == 0) {
        reset_graph<node>(maze);
        maze[start.x][start.y]->wt=0;
        min_length = shortest_path<node>(maze[start.x][start.y], maze[end.x][end.y]);
        return min_length;
    } else if (cp_s_left == 1) {
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