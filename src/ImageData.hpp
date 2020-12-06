#ifndef IMAGEDATA_HPP
#define IMAGEDATA_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

using namespace std;

class ImageData {
    
    public:
        ImageData(string imgPath);
        cv::Mat image;
        vector<map<int, array<int,2>>> flow_graph;
        array<int, 2> sourceNode;
        array<int, 2> sinkNode;
        int graph_source;
        int graph_sink;
        void Image_To_Flow_Graph(int src_x, int src_y, int sink_x, int sink_y);
        float CalculateWeight(int i, int j, int u, int v);
        void addEdge(int node1, int node2, int edge_weight);
        void addInterPixelEdge(int i, int j, int u, int v);
        bool imageBoundryCheck(int i, int j);
};
#endif