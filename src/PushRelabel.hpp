#ifndef PUSHRELABEL_HPP
#define PUSHRELABEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <set>
#include <stack>

using namespace std;

class PushRelabel {
    public:
        PushRelabel(vector<map<int, array<int,2>>> flow_graph);

        int graph_source;
        int graph_sink;
        vector<int> segmentedImage;
        vector<map<int, array<int,2>>> image_flow_graph;
        vector<int> excess;
        vector<int> height;

        void initiate_algorithm();
        void preflow(set<int>& excessNodes);
        void push(int u, int v, set<int>& excessNodes);
        void getAugmentingPaths(vector<int>& path, set<int>& accessibleNodes);
        void getPath(vector<int>& path,const map<int,int>& visited);
        void makeSegmentation(set<int> accessibleNodes);
};
#endif