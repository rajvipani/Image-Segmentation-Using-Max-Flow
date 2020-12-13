#include "ImageData.hpp"
#include "EdmondKarp.hpp"


int edmondk(char *file, char out_file[256], char time[128], char iter[128])
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
    cout << "CORDINATES"<<endl;
    cout << file << endl;
    cout << src_x << " "<< src_y <<endl;
    cout << sink_x << " "<< sink_y <<endl;

    string imageName(image_name);
    string algorithmChoice = "edmond-karp";
    
    ImageData img(imageName);

    if (img.image.rows<src_x || img.image.rows<sink_x){
        cout << "ERROR: Coordinates exceed image dimentions"<<endl;
        return 1;
    }
    else if (img.image.cols<src_y || img.image.rows<sink_y){
        cout << "ERROR: Coordinates exceed image dimentions"<<endl;
        return 1;
    }

    cout << "CORDINATES"<<endl;
    cout << src_x << " "<< src_x <<endl;
    cout << sink_x << " "<< sink_x <<endl;
    img.Image_To_Flow_Graph(src_x, src_y, sink_x, sink_y);

    char* path = realpath(image_name, NULL);
    string abspath(path);

    string directory;
    const size_t last_slash_idx = abspath.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = abspath.substr(0, last_slash_idx);
    }

    string dstname("output_ek.png");
    string out_file_str = directory+"/"+dstname;
    strncpy(out_file, out_file_str.c_str(),256);


    if (algorithmChoice == "edmond-karp") {
        std::cout<<"\nRunning Edmond - Karp's Algorithm\n";
        EdmondKarp ek(img.flow_graph);
        startt = clock(); 
        iterl = ek.initiate_algorithm();
        endt = clock();
        TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
        printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
        img.saveImage(ek.segmentedImage, out_file_str);
    }

    snprintf(time, 128, "%f", (float)TT2);
    snprintf(iter, 128, "%d", iterl);


    return 0;
}



extern "C" {
    int edmondk_c(char *file, char outfile[256], char time[128], char iter[128]){
         return edmondk(file,outfile,time,iter); 
     };
}