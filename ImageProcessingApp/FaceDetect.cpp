// FaceDetect.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageProcessing.h"

using namespace std;
using namespace cv;
using namespace ip;


/** Global variables */
string window_name = "Face detection";
//RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
	ImageProcessing service;
	service.splitData("P<UTOERIKSSON<<ANNA<MARIA<<<<<<<<<<<<<<<<<<<", "L898902C<3UTO6908061F9406236ZE184226B<<<<<14");

	//Read image
	const char * image = "data\\MyPic4.JPG";
	Mat frame = imread(image);

	if(frame.empty())
	{
		cout << "Error loading " << image << " file." << endl;
		return 1;
	}

	//show the image
	imshow(window_name, frame);

	service.detectAndCropFace(frame);

	Mat fram2 = imread("data\\MyPic.jpg");
	//show the image
	imshow(window_name, fram2);
	service.cropSection(fram2, 10,20,100,75);

	waitKey(0);
    return 0;
}