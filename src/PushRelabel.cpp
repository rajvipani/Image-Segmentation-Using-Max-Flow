#include "PushRelabel.hpp"

PushRelabel::PushRelabel(vector<map<int, array<int,2>>> flow_graph) {
    image_flow_graph = flow_graph;
    graph_source = flow_graph.size() - 2;
    graph_sink = flow_graph.size() - 1;

    segmentedImage.resize(flow_graph.size());
    excess.resize(flow_graph.size());
    height.resize(flow_graph.size());
    fill(segmentedImage.begin(), segmentedImage.end(), false);
    fill(excess.begin(), excess.end(), 0);
    fill(height.begin(), height.end(), 0);
    height[graph_source] = image_flow_graph.size();
}

int PushRelabel::initiate_algorithm() {
    set<int> excessNodes;
    preflow(excessNodes);
    bool isMaxHeightNode = true;
    int max_height_node;
    int next_node;
    int iter = 0;
    while(true) {

        if(isMaxHeightNode && excessNodes.size()!=0) {
            int currentMaxHeight = INT_MIN;
            for(auto currNode:excessNodes) {
                if(height[currNode]>currentMaxHeight) {
                    currentMaxHeight = height[currNode];
                    max_height_node = currNode;
                }
            }
        }
        
        if(excessNodes.size() == 0) {
            set<int> accessible_nodes;
            vector<int> path;
            getAugmentingPaths(path, accessible_nodes);
            makeSegmentation(accessible_nodes);
            break;
        }

        for(auto edge:image_flow_graph[max_height_node]) {
            if(((edge.second[0]-edge.second[1]) > 0) && (height[max_height_node] == height[edge.first]+1)) {
                next_node = edge.first;  
                goto jump_for_end_of_loop;
            }
        }
        next_node = max_height_node;

        jump_for_end_of_loop:
        if(next_node != max_height_node) {
            push(max_height_node, next_node, excessNodes);
            isMaxHeightNode = true;
        } else {
            height[max_height_node] += 1;
            isMaxHeightNode = false;
        }

        iter += 1;
    }
    cout << "Number of iterations :" << iter << endl;
    return iter;
}

void PushRelabel::preflow(set<int>& excessNodes) {

    for(auto currentEdge:image_flow_graph[graph_source]) {
        push(graph_source, currentEdge.first, excessNodes);
    }
}

void PushRelabel::push(int u, int v, set<int>& excessNodes) {
    int remainingCapacity = image_flow_graph[u][v][0] - image_flow_graph[u][v][1];
    int d = 0;
    if (u == graph_source) {
        d = remainingCapacity;
    } else {
        d = min(excess[u], remainingCapacity);
    }

    if( (v != graph_sink) && (v != graph_source)) {
        excessNodes.insert(v);
    }
    if((remainingCapacity >= excess[u]) && (u != graph_source) && (u != graph_sink)) {
        excessNodes.erase(u);
    }
    image_flow_graph[u][v][1] += d;
    image_flow_graph[v][u][1] -= d;
    excess[v] += d;
    excess[u] -= d;
}


// Code same as Edmond Karp

void PushRelabel::getAugmentingPaths(vector<int>& path, set<int>& accessibleNodes) {
    stack<int> s;
    map<int, int> visited;

    s.push(graph_source);
    visited.insert({graph_source, graph_source});

    while(!s.empty()) {
        
        int current = s.top();
        s.pop();
        if (current == graph_sink) {
            path.reserve(visited.size());
            getPath(path, visited);
            break;
        }

        for(auto& next_node_values : image_flow_graph[current]) {
            if(visited.find(next_node_values.first) == visited.end()) {
                if((next_node_values.second[0]-next_node_values.second[1]) > 0) {
                    s.push(next_node_values.first);
                    visited.emplace(next_node_values.first, current);
                }
            }
        }
    }
    for(auto& visited_node:visited) {   
        accessibleNodes.insert(visited_node.first);
    }
}

void PushRelabel::getPath(vector<int>& path,const map<int,int>& visited) {
    int next_node = graph_sink;
    path.emplace_back(next_node);
    while(next_node != graph_source) {
        auto temp = visited.find(next_node);
        next_node = temp->second;
        path.emplace_back(next_node);
    }
}

void PushRelabel::makeSegmentation(set<int> accessibleNodes) {
    for(auto node:accessibleNodes) {
        segmentedImage[node] = true;
    }
}
