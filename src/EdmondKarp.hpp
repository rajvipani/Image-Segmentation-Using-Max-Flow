#ifndef EDMONDKARP_HPP
#define EDMONDKARP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

using namespace std;


class EdmondKarp {
    public:
        EdmondKarp(vector<map<int, array<int,2>>> flow_graph);
        
        vector<int> segmentedImage;
        vector<map<int, array<int,2>>> image_flow_graph;
        void initiate_algorithm();
};

#endif