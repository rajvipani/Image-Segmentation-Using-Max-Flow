#include "ImageData.hpp"

ImageData::ImageData(string imgPath) {
    image = cv::imread(imgPath, 0);
    
}

void ImageData::Image_To_Flow_Graph(int src_x, int src_y, int sink_x, int sink_y) {
    
    int img_rows = image.rows;
    int img_cols = image.cols;
    int no_of_vertex = (img_rows * img_cols) + 2;
    graph_source = no_of_vertex - 2;
    graph_sink = no_of_vertex - 1;
    flow_graph.resize((image.rows * image.cols) + 2);
    //To Be replaced by user selecting points
    sourceNode[0] = src_x;
    sourceNode[1] = src_y;
    sinkNode[0] = sink_x;
    sinkNode[1] = sink_y;
    for (int i = 0; i < img_rows; i++) {
        for(int j = 0 ; j < img_cols; j++) {
            float source_to_pixel_weight = CalculateWeight(i, j, sourceNode[0], sourceNode[1]);
            int pixelLinearValue = i * img_cols + j;
            addEdge(graph_source, pixelLinearValue, source_to_pixel_weight);
            float sink_to_pixel_weight = CalculateWeight(i, j, sinkNode[0], sinkNode[1]);
            //std::cout<<source_to_pixel_weight<<" "<<sink_to_pixel_weight<<"\n";
            addEdge(pixelLinearValue, graph_sink, sink_to_pixel_weight);
            addInterPixelEdges(i,j);
        }
    }
    // int j = 0;
    // for(int i = 0; i < flow_graph.size(); i++) {
    //     map<int, array<int,2>> myMap = flow_graph.at(i);
    //     for(auto it = myMap.cbegin(); it != myMap.cend(); ++it) {
    //         std::cout << it->first<<" "<<it->second[0]<<" "<<it->second[1] << "\n";
    //         j += 1;
    //     }
        
    // }
    // std::cout << j<< "\n";
}

float ImageData::CalculateWeight(int i, int j, int u, int v) {
    int sigma = 30;
    int intensity_difference = std::abs(image.at<uint8_t>(i,j)-image.at<uint8_t>(u,v));
    float weight =  100*exp(-pow(intensity_difference,2)/(2*pow(sigma,2)));
    return weight;
}

void ImageData::addEdge(int node1, int node2, int edge_weight) {
    flow_graph[node1][node2]= array<int,2>({static_cast<int>(edge_weight),static_cast<int>(0)});
    if(flow_graph[node2].find(node1) == flow_graph[node2].end()) {
        flow_graph[node2][node1]= array<int,2>({static_cast<int>(0),static_cast<int>(0)});
    }
}

void ImageData::addInterPixelEdges(int i, int j) {
        makeEdge(i,j, i+1, j);
        makeEdge(i,j, i, j-1);
        makeEdge(i,j, i-1, j);
        makeEdge(i,j, i, j+1);    
}

void ImageData::makeEdge(int i, int j, int u, int v) {
    if(imageBoundryCheck(i,j) && imageBoundryCheck(u,v)) {
        float inter_pixel_weight = CalculateWeight(i, j, u, v);
        int pixel1_linearValue = i * image.cols + j;
        int pixel2_linearValue = u * image.cols + v;
        addEdge(pixel1_linearValue, pixel2_linearValue, inter_pixel_weight);
    }
}

bool ImageData::imageBoundryCheck(int i, int j) {
    if (i >= 0 && i < image.rows && j >= 0 && j < image.cols) {
        return true;
    }
    return false;
}

void ImageData::saveImage(vector<int> segmentedImage) {
    cv::Mat mask(image.rows, image.cols, CV_8UC1);

    for(int i=0;i<segmentedImage.size()-2;++i) {
        int u = floor(i/image.cols);
        int v = i%image.cols;
        if(segmentedImage[i]==true)
        {
            mask.at<uint8_t>(u,v) = 255;
        }
        else if(segmentedImage[i]==false)
        {
            mask.at<uint8_t>(u,v) = 0;
        }
        
    }
    std::cout<<"Saving Image..\n";
    cv::imwrite("output_ek.png",mask);   
}