#include "ImageData.hpp"
#include "EdmondKarp.hpp"
#include "PushRelabel.hpp"

int pushr(char *file, char out_file[256], char time[128], char iter[128])
{

    FILE *fp1;
    char image_name[256];
    int n = 0;
    int iterl = 0;
    int src_x, src_y, sink_x, sink_y;
    double TT2;
    clock_t startt, endt; 
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
    string algorithmChoice = "push-relabel";
    
    ImageData img(imageName);
    cv::Mat dest;
    // if (img.image.rows > 50 || img.image.cols > 50){
    // cv::resize(img.image,dest,cv::Size(50,50),0,0,cv::INTER_CUBIC);
    // img.image = dest;      
    // }
    cout << "CORDINATES"<<endl;
    cout << file << endl;
    cout << src_x << " "<< src_y <<endl;
    cout << sink_x << " "<< sink_y <<endl;

    if (img.image.rows<src_x || img.image.rows<sink_x){
        cout << "ERROR: Coordinates exceed image dimentions"<<endl;
        return 1;
    }
    else if (img.image.cols<src_y || img.image.rows<sink_y){
        cout << "ERROR: Coordinates exceed image dimentions"<<endl;
        return 1;
    }

    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    //cv::namedWindow("Display window", 1);
    //cv::imshow("Display window", img.image);

    char* path = realpath(image_name, NULL);
    string abspath(path);

    string directory;
    const size_t last_slash_idx = abspath.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = abspath.substr(0, last_slash_idx);
    }

    string dstname("output_pr.png");
    string out_file_str = directory+"/"+dstname;
    strncpy(out_file, out_file_str.c_str(),256);

    if (algorithmChoice == "edmond-karp") {
        std::cout<<"\nRunning Edmond - Karp's Algorithm\n";
        EdmondKarp ek(img.flow_graph);
        ek.initiate_algorithm();
        img.saveImage(ek.segmentedImage, out_file_str);
    }    
    else if (algorithmChoice == "push-relabel") {
        std::cout<<"\nRunning Push - Relabel Algorithm\n";
        PushRelabel pr(img.flow_graph);
        startt = clock(); 
        iterl = pr.initiate_algorithm();
        endt = clock();
        TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
        printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
        img.saveImage(pr.segmentedImage, out_file_str);
    }
    snprintf(time, 128, "%f", (float)TT2);
    snprintf(iter, 128, "%d", iterl);

    return 0;
}



extern "C" {
    int pushr_c(char *file, char outfile[256], char time[128], char iter[128]){
         return pushr(file,outfile,time,iter); 
     };
}