#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int file_read(char *file, char out_file[256]);
int kmeans_clusering(char *file, char out_file[256]);


int main(int argc, char *argv[])
{
    Mat ocv = imread("rabbit.jpg",IMREAD_GRAYSCALE);
    Mat data;
    ocv.convertTo(data,CV_32F);
    data = data.reshape(1,data.total());
    Mat labels, centers;
    kmeans(data, 2, labels, TermCriteria(CV_TERMCRIT_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    // reshape both to a single row of Vec3f pixels:
    centers = centers.reshape(1,centers.rows);
    data = data.reshape(1,data.rows);

// replace pixel values with their center value:
float *p = data.ptr<float>();
for (size_t i=0; i<data.rows; i++) {
   int center_id = labels.at<int>(i);
   p[i] = centers.at<float>(center_id);
}

// back to 2d, and uchar:
ocv = data.reshape(1, ocv.rows);
ocv.convertTo(ocv, CV_8U);
imshow("Display window", ocv);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("rabbittest.png", ocv);
    }
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
    char outfile[256];
    //file = ;
    //file_read(file,outfile);
    kmeans_clusering(file,outfile);
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
    data = data.reshape(1,img.rows);

    float* p = data.ptr<float>();
    for (size_t i=0; i<data.rows; i++) {
        int center_id = labels.at<int>(i);
        p[i] = centers.at<float>(center_id);
    }

    img = data.reshape(1, img.rows);
    img.convertTo(img, CV_8U);


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


int kmeans_clusering(char *file, char out_file[256]){

    FILE *fp1;
    char image_name[256];
    int n = 0;
    fp1 = fopen(file,"r");
    if (fp1 == NULL) {
        printf("Did not find input file \n");
        exit(1);
    }
    fscanf(fp1,"%s",image_name);
    fclose(fp1);
    cout << image_name <<endl;
    Mat ocv = imread(image_name, IMREAD_GRAYSCALE);
    if(ocv.empty())
    {
        std::cout << "Could not read the image: " << image_name << std::endl;
        return 1;
    }
// src - foreground
//    sink - background


    Mat data;
    ocv.convertTo(data,CV_32F);
    data = data.reshape(1,data.total());
    Mat labels, centers;
    kmeans(data, 2, labels, TermCriteria(CV_TERMCRIT_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    // reshape both to a single row of Vec3f pixels:
    centers = centers.reshape(1,centers.rows);
    data = data.reshape(1,data.rows);

    // replace pixel values with their center value:
    float *p = data.ptr<float>();
    for (size_t i=0; i<data.rows; i++) {
       int center_id = labels.at<int>(i);
       p[i] = centers.at<float>(center_id);
    }

    // back to 2d, and uchar:
    ocv = data.reshape(1, ocv.rows);
    ocv.convertTo(ocv, CV_8U);

    char* path = realpath(image_name, NULL);
    string abspath(path);

    string directory;
    const size_t last_slash_idx = abspath.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = abspath.substr(0, last_slash_idx);
    }

    string dstname("rabbit_kmeans.png");
    string out_file_str = directory+"/"+dstname;
    imwrite(out_file_str, ocv);
    strncpy(out_file, out_file_str.c_str(),256);

    return 0;

}


int file_read(char *file, char out_file[256]){
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

    std::string image_path;
    image_path = samples::findFile(image_name);      
    cout << "FROM CPP" <<endl; 

    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        char error[] = "ERROR";
        return 1;
    }
    //imshow("Display window", img);

    char* path = realpath(image_name, NULL);
    string abspath(path);

    string directory;
    const size_t last_slash_idx = abspath.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = abspath.substr(0, last_slash_idx);
    }

    string dstname("rabbit2.png");
    string out_file_str = directory+"/"+dstname;
    imwrite(out_file_str, img);
    strncpy(out_file, out_file_str.c_str(),256);

    printf("OUTPUT FILE: %s\n",out_file);
    return 0;
}


extern "C" {
    int test_funcc(){ return test_func(); };
    int file_read_c(char *file, char outfile[256]){ 
         //printf("WORKING CPP\n");
         return file_read(file,outfile); 
     };
    int kmeans_clustering_c(char *file, char outfile[256]){
         return kmeans_clusering(file,outfile); 
     };
}
