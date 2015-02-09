#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

#define ESC_KEY (27)

int main(int argc, char **argv)
{
    Mat basicimage, dst;
    int frameCnt=0;
    
    
    // read in image
    if(argc < 2){
    	
    	printf("\n\r Using default images \n\r");
	    basicimage = imread("Cactus360p.jpg", CV_LOAD_IMAGE_COLOR);
		
	}
	
	else {
	
		basicimage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	}
	
    if(!basicimage.data)  // Check for invalid input
    {
        printf("Could not open or find the refernece starting image\n");
        exit(-1);
    }
    
	 // interactive computer vision window
    namedWindow("Borders and cross hairs", CV_WINDOW_AUTOSIZE);
    
    dst = basicimage;
    
	imshow("Borders and cross hairs", basicimage);

    // Interactive LOOP
   
   	//IplImage basicimageImg = basicimage;
   	
   	//size_t size = sizeof(basicimage.imagedata);
   	int row, col;
   	row = basicimage.rows;
   	col = basicimage.cols;
   	
   	printf("Rows: %d, cols: %d\n", basicimage.rows, basicimage.cols);
   	
   	int i, j;
   	
	for(i = 0; i < basicimage.rows; i++){
	
		for(j = 0; j < basicimage.cols; j++){
			
			if(i == (basicimage.rows)/2 || j == (basicimage.cols)/2){
			
				 Vec3b color = basicimage.at<Vec3b>(Point(j,i));

                color[0] = 0; //B
                color[1] = 255; //G
                color[2] = 255; //R
		        // set pixel
		        basicimage.at<Vec3b>(Point(j,i)) = color;
			
			}
		}
	}
   	
   	
    while(1)
    {
       
        // set pace on shared memory sampling in msecs
        char c = cvWaitKey(10);

        if(c == ESC_KEY)
        {
            exit(1);
        }
        
		copyMakeBorder( basicimage, dst, 4, 4, 4, 4, BORDER_CONSTANT, 255 );
		imshow("Borders and cross hairs", dst);
		
    }
 
    return 0;

}
