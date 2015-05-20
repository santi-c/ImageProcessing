#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageProcessing.h"

using namespace std;
using namespace cv;
using namespace ip;

cv::Mat ImageProcessing::detectAndCropFace(Mat img){

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
	
	//Cropped Imag
	Mat croppedImg;

	//Search faces, Just once in this case
	for(size_t i = 0; i < faces.size(); i++)
	{
		//Crop and save face
		Rect croppedArea(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
		croppedImg = img(croppedArea).clone();
		//Mat croppedImg(img(croppedArea).clone());
		imwrite("data\\cropped.jpg", croppedImg);
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
	return croppedImg;
}

cv::Mat ImageProcessing::cropSection(Mat img, int posX, int posY, int widthX, int heightY){
		//Crop and save face
		Rect croppedArea(posX, posY, widthX, heightY);
		Mat croppedImg(img(croppedArea).clone());
		imwrite("data\\croppedSection.jpg", croppedImg);
		imshow("CropSection",croppedImg);
		return croppedImg;
}

IdentityDocument ImageProcessing::splitData(string zone1, string zone2){
	//Processing Surnames and Names
	string parseFullName = zone1.substr(5,40);
	std::string delimiter = "<<";
	std::string delimiter2 = "<";
	string surname = parseFullName.substr(0, parseFullName.find(delimiter));
	string name = parseFullName.erase(0, parseFullName.find(delimiter) + delimiter.length());
	//Clean delimiter in surnames
	replace(surname.begin(), surname.end(), '<', ' ');
	//Names
	size_t pos = 0;
	std::string token;
	while((pos = name.find(delimiter2))!= std::string::npos) {
		token += name.substr(0, pos);
		name.erase(0,pos + 1);
		if(name.length()>0 && name.substr(0,1) != delimiter2){
			token += ' '; //add space between names
		}
	}

	IdentityDocument *passport = new IdentityDocument();
	//Zone 1
	passport->setType(zone1.substr(0,1));
	passport->setCountry(zone1.substr(2,3));
	passport->setSurnames(surname);	
	passport->setGivenNames(token);

	//Zone 2
	size_t lenghtId = zone2.find('<');
	passport->setId(zone2.substr(0,lenghtId));
	passport->setCheckId(zone2.substr(9,1));
	passport->setNationality(zone2.substr(10,3));
	passport->setDateBirth(zone2.substr(13,6));
	passport->setCheckBirth(zone2.substr(19,1));
	passport->setSex(zone2.substr(20,1));
	passport->setDateExpiry(zone2.substr(21,6));
	passport->setCheckExpiry(zone2.substr(27,1));
	passport->setOptionalData(zone2.substr(28,zone2.substr(28,14).find(delimiter2)));
	passport->setCheckOptional(zone2.substr(42,1));
	return *passport;
}

