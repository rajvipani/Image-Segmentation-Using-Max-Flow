#include "ImageData.hpp"
#include "EdmondKarp.hpp"
#include "PushRelabel.hpp"

int main(int argc, char *argv[])
{
    int src_x, src_y, sink_x, sink_y;

    src_x = 33;
    src_y = 33;
    sink_x = 15;
    sink_y = 15;

    string imageName = argv[1];
    string algorithmChoice = argv[2];
    
    ImageData img(imageName);
    cv::Mat dest;
    cv::resize(img.image,dest,cv::Size(50,50),0,0,cv::INTER_CUBIC);
    img.image = dest;
    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    char* path = realpath(".", NULL);
    string abspath(path);

    cout << abspath << endl;

    //string directory;
    //const size_t last_slash_idx = abspath.rfind('/');
    //if (std::string::npos != last_slash_idx)
    //{
    //    directory = abspath.substr(0, last_slash_idx);
    //}
    //cout << directory << endl;

    string dstname("output_ek.png");
    string out_file_str = abspath+"/"+dstname;
    cout << out_file_str << endl;
    //imwrite(out_file_str, img);
    //strncpy(out_file, out_file_str.c_str(),256);

    //cv::namedWindow("Display window", 1);
    //cv::imshow("Display window", img.image);

    if (algorithmChoice == "edmond-karp") {
        std::cout<<"\nRunning Edmond - Karp's Algorithm\n";
        EdmondKarp ek(img.flow_graph);
        ek.initiate_algorithm();
        img.saveImage(ek.segmentedImage);

    } else if (algorithmChoice == "push-relabel") {
        std::cout<<"\nRunning Push - Relabel Algorithm\n";
        PushRelabel pr(img.flow_graph);
        pr.initiate_algorithm();
        img.saveImage(pr.segmentedImage);
    }
    return 0;
}