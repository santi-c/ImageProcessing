#include <iostream>
#include "ImageProcessing.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
using namespace ip;

void ImageProcessing::detectAndCropFace(Mat img){

	//Load the cascades to detect face
	String face_cascade_name = "algorithms\\haarcascade_frontalface_alt.xml";
	//String face_cascade_name = "lbpcascade_frontalface.xml";
	CascadeClassifier face_cascade;
	if(!face_cascade.load(face_cascade_name))
	{
		cout << "Error loading haarcascade_frontalface_alt.xml" << endl;
	}

	//Prepare image, gray image
	std::vector<Rect> faces;
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	equalizeHist(img_gray, img_gray);

	//Detect faces in gray image
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
	
	//Search faces, Just once in this case
	for(size_t i = 0; i < faces.size(); i++)
	{
		//Crop and save face
		Rect croppedArea(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
		Mat croppedImg(img(croppedArea).clone());
		imwrite("cropped.jpg", croppedImg);
		imshow("Crop",croppedImg);

		// draw the box detect
		rectangle(img, 
			Point(faces[i].x, faces[i].y),//up left
			Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
			Scalar(0,0,255),// line color
			2 //line size
			);
	}

	//Display image with face detect
	imshow("FaceDetect", img);
}