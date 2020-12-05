#include "EdmondKarp.hpp"

EdmondKarp::EdmondKarp(vector<map<int, array<int,2>>> flow_graph) {
    image_flow_graph = flow_graph;
    segmentedImage.resize(flow_graph.size());
}

void EdmondKarp::initiate_algorithm() {
    
}