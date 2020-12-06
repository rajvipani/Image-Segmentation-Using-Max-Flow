#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

//define tree by edge and vertices
struct Edge {
   int flow;
   int capacity; 
   //start and end vertices 
   int u, v;

   Edge(int flow, int capacity, int u, int v) {
       this -> flow = flow;
       this -> capacity = capacity;
       this -> u = u;
       this -> v = v;
   }
};

//represent vertices
struct Vertex {
    int h;
    int e_flow;

    Vertex(int h, int e_flow) {
        this-> h = h;
        this -> e_flow = e_flow;
    }
};

//define a graph
class Graph {
    int N; //number of nodes
    vector<Vertex> node;
    vector<Edge> arc;

    //FUNCTIONS
    //push excess flow
    bool push(int u);
    //relabel vertex u
    void relabel(int u);
    //initialize preflow
    void preflow(int s);
    //reverse edge
    void update_reverse(int i, int flow);

    public:
    //constructor:
    Graph(int N);
    //add egde to a graph:
    void addEdge(int u, int v, int w);
    //max flow between two nodes
    int Push_Relabel(int s, int t);
};

Graph::Graph(int N) {
    this-> N = N;
    //nodes initialized with zero height and zero flow 
    for (int i = 0; i < N; i++) {
        node.push_back(Vertex(0,0));
    }
}

void Graph::addEdge(int u, int v, int capacity) {
    //flow initialized to zero for all arcs 
    arc.push_back(Edge(0, capacity,u, v));
}

void Graph::preflow(int s) {
    //h source vertex = number of nodes
    node[s].h = node.size();

    for (int i = 0; i < arc.size(); i++) {
        //check if currente arc goes from source
        if (arc[i].u == s) {
          arc[i].flow = arc[i].capacity;
          //initialize excess flow for adjacent node v
          node[arc[i].v].e_flow += arc[i].flow;
          // add edge from v to s with zero capacity
          arc.push_back(Edge(-arc[i].flow, 0, arc[i].v, s));
        }
    }
}

//index of overflowing vertex
int overFlow(vector<Vertex>& node) {
    for (int i = 1; i < node.size() - 1; i++) {
        if (node[i].e_flow > 0) {
            return i;
        }
        else {
            return -1; //no overflow node
        }
    }
}

void Graph::update_reverse(int i, int flow) {
    int u = arc[i].v, v = arc[i].u;
    for (int j = 0; j < arc.size(); j++) {
        if (arc[j].v == v && arc[j].u == u) {
            arc[j].flow  -= flow;
            return;
        }
    }
    //add reverse arc in residual graph
    Edge e = Edge(0, flow, u, v);
    arc.push_back(e);
}

//push flow
bool Graph::push(int u) {
    //find adjacent node to u to which flow can be pushed
    for (int i = 0; i < arc.size(); i++) {
        if (arc[i].u == u) {
          //flow = capacity --> no push is possible
          if (arc[i].flow == arc[i].capacity) {
              continue;
          }
          //flow if nieghbor node's height is less than overflowing vertex
          if (node[u].h > node[arc[i].v].h) {
              int flow = min(arc[i].capacity - arc[i].flow, node[u].e_flow);
              //reduce excess flow
              node[u].e_flow -= flow;
              //increase excess flow adjacent node
              node[arc[i].v].e_flow += flow;
              //add residual flow
              arc[i].flow += flow;

              update_reverse(i, flow);

              return true;
            }
        }
    }

    return false;
}

//relabel vertex
void Graph::relabel(int u){
    //initialize min height
    int minheight = INT_MAX;

    //find neighbor with minimum height
    for (int i = 0; i < arc.size(); i++) {
        if (arc[i].u == u) {
            if (arc[i].flow == arc[i]. capacity) {
               continue; 
            }
            //update min height
            if (node[arc[i].v].h < minheight) {
                minheight = node[arc[i].v].h;
                //updtae height of u
                node[u].h = minheight + 1;
            }
        }
    }
}

//print maxflow
int Graph::Push_Relabel(int s, int t) {
    preflow(s);
    //no node overflow
    while (overFlow(node) != -1) {
        int u = overFlow(node);
        if (!push(u)) {
            relabel(u);
        }
    }

    return node.back().e_flow;
}





