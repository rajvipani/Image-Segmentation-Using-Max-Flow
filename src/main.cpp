#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    std::string image_path;
    if (argc==2){
        image_path = samples::findFile(argv[1]);
    }
    else{
        image_path = samples::findFile("rabbit.jpg");       
    }

    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("rabbit.png", img);
    }
    return 0;
}