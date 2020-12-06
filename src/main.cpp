#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int file_read(char *file);

int main(int argc, char *argv[])
{
    // std::string image_path;
    // if (argc==2){
    //     image_path = samples::findFile(argv[1]);
    // }
    // else{
    //     image_path = samples::findFile("rabbit.jpg");       
    // }

    // Mat img = imread(image_path, IMREAD_GRAYSCALE);
    // if(img.empty())
    // {
    //     std::cout << "Could not read the image: " << image_path << std::endl;
    //     return 1;
    // }
    // //imshow("Display window", img);

    // Mat ocv = img;

    // Mat data;
    // img.convertTo(data,CV_32F);
    // Mat labels, centers;

    // kmeans(data, 2, labels, TermCriteria(1, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    // centers = centers.reshape(1,centers.rows);
    // data = data.reshape(1,data.rows);
    char file[128] = "image_data.txt";
    //file = ;
    file_read(file);
/*
    // replace pixel values with their center value:
    Vec1f *p = data.ptr<Vec1f>();
    for (size_t i=0; i<data.rows; i++) {
       int center_id = labels.at<int>(i);
       p[i] = centers.at<Vec1f>(center_id);
    }
*/
/*
    ocv = data.reshape(1, ocv.rows);

    ocv.convertTo(ocv, CV_8U);

    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("rabbit.png", img);
    }
*/
    return 0;
}





int test_func(){
    std::string image_path;
        image_path = samples::findFile("rabbit.jpg");      
        cout << "FROM CPP" <<endl; 

    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    //imshow("Display window", img);

    Mat ocv = img;

    Mat data;
    img.convertTo(data,CV_32F);
    Mat labels, centers;

    kmeans(data, 2, labels, TermCriteria(1, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    centers = centers.reshape(1,centers.rows);
    data = data.reshape(1,data.rows);

    // replace pixel values with their center value:
    //Vec1f *p = data.ptr<Vec1f>();
    //for (size_t i=0; i<data.rows; i++) {
    //   int center_id = labels.at<int>(i);
    //   p[i] = centers.at<Vec1f>(center_id);
    //}


    //ocv = data.reshape(1, ocv.rows);

    //ocv.convertTo(ocv, CV_8U);

    //int k = waitKey(0); // Wait for a keystroke in the window
    //if(k == 's')
    //{
    //    imwrite("rabbit.png", img);
    //}
    return 0;
}


int file_read(char *file){
    printf("File %s \n",file);
    FILE *fp1;
    char image_name[256];
    int n = 0;
    fp1 = fopen(file,"r");
    if (fp1 == NULL) {
        printf("Did not find input file \n");
        exit(1);
    }
    fscanf(fp1,"%s",image_name);
    fscanf(fp1,"%d",&n); 
    printf("Image: %s\n",image_name);
    printf("Number of points: %d\n",n);
    fclose(fp1);
    return 0;
}


extern "C" {
    int test_funcc(){ return test_func(); };
    int file_read_c(char *file){ 
         printf("WORKING CPP\n");
         return file_read(file); 
     };
}
