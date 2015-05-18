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


///** Global variables */
//String face_cascade_name = "haarcascade_frontalface_alt.xml";
////String face_cascade_name = "lbpcascade_frontalface.xml";
//String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
//CascadeClassifier face_cascade;
////CascadeClassifier eyes_cascade;
string window_name = "Face detection";
//RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
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

	ImageProcessing service;
	service.detectAndCropFace(frame);

	Mat fram2 = imread("data\\MyPic.jpg");
	//show the image
	imshow(window_name, fram2);
	service.cropSection(fram2, 10,20,100,75);


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
