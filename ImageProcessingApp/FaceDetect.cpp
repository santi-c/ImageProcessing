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

	//Read image
	Mat inputImage = imread(image, CV_LOAD_IMAGE_GRAYSCALE);
	if(inputImage.empty()){
		cout << "Error loading " << image << " file." << endl;
		return 1;
	}

	//show the image
	namedWindow(window_name, CV_WINDOW_NORMAL);
	imshow(window_name, inputImage);

	//----- Service -------//
	ImageProcessing service;
	//Set path, directory and default fileName
	service.setPath(image);
	//Passport Template, set design -> 1 = Indio, 2 = USA (Default)
	service.setTemplate(new Template(inputImage, 1));
	//Data from Image and output
	IdentityDocument idDoc;
	if(service.getTextFromImage(inputImage, idDoc))
	{
		//Zone 1
		cout << "Type: " << idDoc.getType() << endl;
		cout << "Country: " << idDoc.getCountry() << endl;
		cout << "Surnames: " << idDoc.getSurnames() << endl;
		cout << "Given names: " << idDoc.getGivenNames() << endl;

		//Zone 2
		cout << "Id: " << idDoc.getId() << endl;
		cout << "CheckId: " << idDoc.getCheckId() << endl;
		cout << "Nationality: " << idDoc.getNationality() << endl;
		cout << "Birth date: " << idDoc.getDateBirth() << endl;
		cout << "Birth check: " << idDoc.getCheckBirth() << endl;
		cout << "Sex: " << idDoc.getSex() << endl;
		cout << "Date expiry: " << idDoc.getDateExpiry() << endl;
		cout << "Check expiry: " << idDoc.getCheckExpiry() << endl;
		cout << "Optional data: " << idDoc.getOptionalData() << endl;
		cout << "Check optional: " << idDoc.getCheckOptional() << endl;
		cout << "Check overall: " << idDoc.getCheckOverall() << endl;

	}
	//Detect, crop and show Face
	service.cropSection(inputImage, service.detectFace(inputImage), "Face");
	//Signature, crop and show
	service.cropSection(inputImage,service.getTemplate()->getSignature(), "Signature");

	waitKey(0);
    return 0;
}
