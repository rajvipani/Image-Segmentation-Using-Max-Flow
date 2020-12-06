#include "ImageData.hpp"
#include "EdmondKarp.hpp"

int main(int argc, char *argv[])
{
    // std::string image_path;
    // if (argc==2){
    //     image_path = samples::findFile(argv[1]);
    // }
    // else{
    //     image_path = samples::findFile("rabbit.jpg");       
    // }

    // //Mat img = imread(image_path, IMREAD_GRAYSCALE);
    // if(img.empty())
    // {
    //     std::cout << "Could not read the image: " << image_path << std::endl;
    //     return 1;
    // }
   // cv::Mat imgn;
    //cv::resize(inImg, outImg, cv::Size(), 0.75, 0.75);
    string imageName = argv[1];
    //string algorithmChoice = argv[2];
    
    ImageData img(imageName);
    img.Image_To_Flow_Graph();


    cv::namedWindow("Display window", 1);
    cv::imshow("Display window", img.image);
    int k = cv::waitKey(0);

    //if (algorithmChoice == "edmond-karp") {
        std::cout<<"\nRunning Edmond - Karp's Algorithm\n";
        EdmondKarp ek(img.flow_graph);
        ek.initiate_algorithm();
    //}
    //int k = cv::waitKey(0);
    // if(k == 's')
    // {
    //     imwrite("rabbit.png", img);
    // }
    return 0;
}