#ifndef EDMONDKARP_HPP
#define EDMONDKARP_HPP

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <set>
#include <stack>
#include <assert.h>

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
        void getPath(vector<int>& path,const std::map<int,int>& visited);
        void makeSegmentation(set<int> accessibleNodes);
};

#endif