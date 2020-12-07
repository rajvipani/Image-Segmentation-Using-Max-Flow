#include "ImageData.hpp"
#include "EdmondKarp.hpp"

int edmondk(char *file, char out_file[256])
{

    FILE *fp1;
    char image_name[256];
    int n = 0;
    int src_x, src_y, sink_x, sink_y;
    fp1 = fopen(file,"r");
    if (fp1 == NULL) {
        printf("Did not find input file \n");
        exit(1);
    }
    fscanf(fp1,"%s",image_name);
    fscanf(fp1,"%d",&n);
    fscanf(fp1,"%d, %d",&sink_x,&sink_y);
    fscanf(fp1,"%d, %d",&src_x,&src_y);
    fclose(fp1);
    cout << image_name <<endl;
    cv::Mat ocv = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
    if(ocv.empty())
    {
        std::cout << "Could not read the image: " << image_name << std::endl;
        return 1;
    }

    string imageName(image_name);
    string algorithmChoice = "edmond-karp";
    
    ImageData img(imageName);
    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    //cv::namedWindow("Display window", 1);
    //cv::imshow("Display window", img.image);

    if (algorithmChoice == "edmond-karp") {
        std::cout<<"\nRunning Edmond - Karp's Algorithm\n";
        EdmondKarp ek(img.flow_graph);
        ek.initiate_algorithm();
        img.saveImage(ek.segmentedImage);
    }

    char* path = realpath(".", NULL);
    string abspath(path);
    string dstname("output_ek.png");
    string out_file_str = abspath+"/"+dstname;
    strncpy(out_file, out_file_str.c_str(),256);
    //int k = cv::waitKey(0);
    // if(k == 's')
    // {
    //     imwrite("rabbit.png", img);
    // }
    return 0;
}



extern "C" {
    int edmondk_c(char *file, char outfile[256]){
         return edmondk(file,outfile); 
     };
}