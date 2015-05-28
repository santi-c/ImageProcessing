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
	const char * image;

	if(argc > 1)
	{
		image = argv[1];
	}
	else
	{
		cerr << "ERROR: Missing file argument" << endl;
		return 1;
	}
	
	//----- Service -------//
	ImageProcessing service;
	
	if(!service.getCustomerInfo(image))
	{
		cout << "Error processing image" << endl;
	}

	waitKey(0);
    return 0;
}
