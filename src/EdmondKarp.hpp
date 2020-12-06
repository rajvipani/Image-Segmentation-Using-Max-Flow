#ifndef EDMONDKARP_HPP
#define EDMONDKARP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <set>
#include <stack>
enum edge_variables_for_original_graph{capacity,flow};
using namespace std;

class EdmondKarp {
    public:
        EdmondKarp(vector<map<int, array<int,2>>> flow_graph);
        int graph_source;
        int graph_sink;
        vector<int> segmentedImage;
        vector<map<int, array<int,2>>> image_flow_graph;
        void initiate_algorithm();
        void getAugmentingPaths(vector<int>& path, set<int>& accessibleNodes);
        void getFlowInAugmentingPath(vector<int>& path, int& flow_p);
        void augmentFlow(vector<int>& path, int& flow_p);
};

#endif