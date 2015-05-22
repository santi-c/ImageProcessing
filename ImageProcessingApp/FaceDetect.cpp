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

	if(inputImage.empty())
	{
		cout << "Error loading " << image << " file." << endl;
		return 1;
	}

	//show the image
	namedWindow(window_name, CV_WINDOW_NORMAL);
	imshow(window_name, inputImage);

	ImageProcessing service;
	service.detectAndCropFace(inputImage);

	///////////////////////////////////////////////////////////////////////////
	// TODO: remove hardcoded rect positions by detection the zone in the image
	const int xPos = static_cast<int>(inputImage.cols * (65.0 / 100.0));
	const int yPos = static_cast<int>(inputImage.rows * (63.0 / 100.0));
	const int width = static_cast<int>(inputImage.cols * (30.0 / 100.0));
	const int height = static_cast<int>(inputImage.rows * (20.0 / 100.0));
	///////////////////////////////////////////////////////////////////////////

	service.cropSection(inputImage, xPos, yPos, width, height);

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

	////-- 1. Load the cascades to detect face
	//if(!face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	////if(!eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

 //  
	////Prepare image, gray image
	//std::vector<Rect> faces;
	//Mat frame_gray;

	//cvtColor( frame, frame_gray, CV_BGR2GRAY );
	//equalizeHist(frame_gray, frame_gray);

	////-- Detect faces in gray image
	//face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
	//
	//// Search faces, Just once in this case
	//for(size_t i = 0; i < faces.size(); i++)
	//{
	//	////Crop and save face
	//	//Rect croppedArea(faces[i].x, faces[i].y, faces[i].x + faces[i].width, faces[i].y + faces[i].height);
	//	//Mat croppedImg(frame(croppedArea).clone());
	//	//imwrite("cropped.jpg", croppedImg);
	//	//imshow("Crop",croppedImg);

	//	// draw the box detect
	//	rectangle(frame, 
	//		Point(faces[i].x, faces[i].y),//up left
	//		Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
	//		Scalar(0,0,255),// line color
	//		2 //line size
	//		);
	//}
	//
	//imshow( window_name, frame );

	waitKey(0);
    return 0;
}
