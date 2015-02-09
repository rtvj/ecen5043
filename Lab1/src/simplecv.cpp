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

#define VRES_ROWS (180)
#define HRES_COLS (320)

#define ESC_KEY (27)

// Buffer for highest resolution visualization possible
unsigned char imagebuffer[1440*2560*3]; // 1440 rows, 2560 cols/row, 3 channel

int main(int argc, char **argv)
{
    int hres = HRES_COLS;
    int vres = VRES_ROWS;
    Mat basicimage(vres, hres, CV_8UC3, imagebuffer);
    Mat A;
    int frameCnt=0;

    printf("hres=%d, vres=%d\n", hres, vres);

    // interactive computer vision loop 
    namedWindow("Profile Visualization", CV_WINDOW_AUTOSIZE);

    // read in default image
    basicimage = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	
    if(!basicimage.data)  // Check for invalid input
    {
        printf("Could not open or find the refernece starting image\n");
        exit(-1);
    }

	printf("rows %d\n", basicimage.rows);
	
	for(int y=0;y<basicimage.rows;y++)
	{
		 for(int x=0;x<basicimage.cols;x++)
		 {
		 
		     if(y < 4 || y > 176 || x < 4 || x > 316 || y == 90 || x == 160)
		     {
		     Vec3b color = basicimage.at<Vec3b>(Point(x,y));

				color[0] = 0; //B
				color[1] = 255; //G
				color[2] = 255; //R
		     // set pixel
		     basicimage.at<Vec3b>(Point(x,y)) = color;
		     }
		     
		  
		 }
	}
	
    // Create an IplImage mapping onto the basicimage Mat object
    //
    IplImage basicimageImg = basicimage;


        frameCnt++;

        // Write a zero value into the image buffer
        //
        basicimageImg.imageData[frameCnt] = (unsigned char)0;

        imshow("Profile Visualization", basicimage);  

        // set pace on shared memory sampling in msecs
        char c = cvWaitKey(10);

        if(c == ESC_KEY)
        {
            exit(1);
        }

	 imwrite("out.jpg",basicimage);
    return 1;

}
