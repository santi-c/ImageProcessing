#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageProcessing.h"


#include "allheaders.h"

using namespace std;
using namespace cv;
using namespace ip;

ImageProcessing::ImageProcessing()
{
  // initilize tesseract OCR engine
  myOCR = new tesseract::TessBaseAPI();

  printf("Tesseract-ocr version: %s\n",
         myOCR->Version());
  printf("Leptonica version: %s\n",
         getLeptonicaVersion());
}

void ImageProcessing::detectAndCropFace(Mat & img){
	//Load the cascades to detect face
	String face_cascade_name = "..\\ImageProcessingApp\\algorithms\\haarcascade_frontalface_alt.xml";
	//String face_cascade_name = "lbpcascade_frontalface.xml";
	CascadeClassifier face_cascade;
	if(!face_cascade.load(face_cascade_name))
	{
		cout << "Error loading haarcascade_frontalface_alt.xml" << endl;
	}

	//Prepare image, gray image
	std::vector<Rect> faces;
	//Mat img_gray;
	//cvtColor(img, img_gray, CV_BGR2GRAY);
	//equalizeHist(img_gray, img_gray);

	//Detect faces in gray image
	face_cascade.detectMultiScale(img, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
	
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
		namedWindow("Cropped face", CV_WINDOW_NORMAL);
		imshow("Cropped face",croppedImg);

		// draw the box detect
		rectangle(img, 
			Point(faces[i].x, faces[i].y),//up left
			Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
			Scalar(0,0,255),// line color
			2 //line size
			);
	}

	//Display image with face detect
	namedWindow("Face Detected", CV_WINDOW_NORMAL);
	imshow("Face Detected", img);
}

void ImageProcessing::cropSection(Mat & img, int posX, int posY, int widthX, int heightY){
	//Crop and save face
	Rect croppedArea(posX, posY, widthX, heightY);
	Mat croppedImg(img(croppedArea).clone());
	imwrite("data\\croppedSection.jpg", croppedImg);

	namedWindow("Cropped section", CV_WINDOW_AUTOSIZE);
	imshow("Cropped section",croppedImg);
}

bool ImageProcessing::getTextFromImage(cv::Mat & img, std::string & firstLine, std::string & secondLine)
{

	if (myOCR->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		return false;
	}

	tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7); // treat the image as a single text line
	myOCR->SetPageSegMode(pagesegmode);

	Mat newImg = img.clone();

	///////////////////////////////////////////////////////////////////////////
	// TODO: remove hardcoded rect positions by detecting the zone in the image
	const int xPos = static_cast<int>(newImg.cols * (2.0 / 100.0));
	const int yPos1 = static_cast<int>(newImg.rows * (80.0 / 100.0));
	const int yPos2 = static_cast<int>(newImg.rows * (87.0 / 100.0));
	const int width = static_cast<int>(newImg.cols * (93.0 / 100.0));
	const int height = static_cast<int>(newImg.rows * (7.0 / 100.0));
	///////////////////////////////////////////////////////////////////////////

	Rect text1ROI(xPos, yPos1, width, height);
	Rect text2ROI(xPos, yPos2, width, height);

	// recognize text in the first line
	myOCR->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ<");
	myOCR->TesseractRect( newImg.data, 1, newImg.step1(), text1ROI.x, text1ROI.y, text1ROI.width, text1ROI.height);
	text1 = myOCR->GetUTF8Text();

	// recognize text in the second line
	myOCR->SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ<");
	myOCR->TesseractRect( newImg.data, 1, newImg.step1(), text2ROI.x, text2ROI.y, text2ROI.width, text2ROI.height);
	text2 = myOCR->GetUTF8Text();

	// remove "newline"
	string t1(text1);
	t1.erase(std::remove(t1.begin(), t1.end(), '\n'), t1.end());
	firstLine = t1;

	string t2(text2);
	t2.erase(std::remove(t2.begin(), t2.end(), '\n'), t2.end());
	secondLine = t2;

	//// print found text
	//printf("found text1: \n");
	//printf(t1.c_str());
	//printf("\n");

	//printf("found text2: \n");
	//printf(t2.c_str());
	//printf("\n");

	// draw text on original image
	//Mat scratch = img.clone();

	//int fontFace = FONT_HERSHEY_PLAIN;
	//double fontScale = 2;
	//int thickness = 2;
	//putText(scratch, t1, Point(text1ROI.x, text1ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);
	//putText(scratch, t2, Point(text2ROI.x, text2ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);

	rectangle(newImg, text1ROI, Scalar(0, 0, 255), 2, 8, 0);
	rectangle(newImg, text2ROI, Scalar(0, 0, 255), 2, 8, 0);

	imshow("tesseract-opencv", newImg);
	//waitKey(0);
	return true;

}

ImageProcessing::~ImageProcessing()
{
  delete [] text1;
  delete [] text2;

  // destroy tesseract OCR engine
  myOCR->Clear();
  myOCR->End();
}

void ImageProcessing::splitData(IdentityDocument & passport, string & zone1, string & zone2){
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
	//Providing token is empty (no delimiters), we have one name
	if(token.length()==0 && name.length())
		token = name;
	//IdentityDocument *passport = new IdentityDocument();
	//Zone 1
	passport.setType(zone1.substr(0,1));
	passport.setCountry(zone1.substr(2,3));
	passport.setSurnames(surname);	
	passport.setGivenNames(token);

	//Zone 2
	size_t lenghtId = zone2.find('<');
	passport.setId(zone2.substr(0,lenghtId));
	passport.setCheckId(zone2.substr(9,1));
	passport.setNationality(zone2.substr(10,3));
	passport.setDateBirth(zone2.substr(13,6));
	passport.setCheckBirth(zone2.substr(19,1));
	passport.setSex(zone2.substr(20,1));
	passport.setDateExpiry(zone2.substr(21,6));
	passport.setCheckExpiry(zone2.substr(27,1));
	passport.setOptionalData(zone2.substr(28,zone2.substr(28,14).find(delimiter2)));
	passport.setCheckOptional(zone2.substr(42,1));

}
