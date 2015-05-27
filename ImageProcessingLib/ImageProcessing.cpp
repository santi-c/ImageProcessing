#include <iostream>
#include <fstream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageProcessing.h"


#include "allheaders.h"

using namespace std;
using namespace cv;
using namespace ip;

static string sep = "_";

ImageProcessing::ImageProcessing() : ID_3_PASSPORT_HEIGHT(88.0), ID_3_PASSPORT_WIDTH(125.0)
{
  // initilize tesseract OCR engine
  myOCR = new tesseract::TessBaseAPI();
}

CvRect ImageProcessing::detectFace(const Mat & srcImg)
{
	Mat img(srcImg.clone());

	//Load the cascades to detect face
	String face_cascade_name = "..\\ImageProcessingApp\\algorithms\\haarcascade_frontalface_alt.xml";

	CascadeClassifier face_cascade;
	if(!face_cascade.load(face_cascade_name))
	{
		cout << "Error loading haarcascade_frontalface_alt.xml" << endl;
	}

	//Prepare image, gray image
	vector<Rect> faces;

	//Detect faces in gray image
	face_cascade.detectMultiScale(img, faces, 1.1, 5, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
	
	//Cropped Imag
	Mat croppedImg;
	CvRect faceSection;
	//Search faces, Just once in this case
	for(size_t i = 0; i < faces.size(); i++)
	{
		faceSection = cvRect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
		//Crop and save face
		//cropSection(img, faces[i].x, faces[i].y, faces[i].width, faces[i].height, "Face");
		/*
		Rect croppedArea(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
		croppedImg = img(croppedArea).clone();
		//Mat croppedImg(img(croppedArea).clone());
		imwrite(directory + "croppedFace.jpg", croppedImg);
		namedWindow("Cropped face", CV_WINDOW_NORMAL);
		imshow("Cropped face",croppedImg);
		*/
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

	return faceSection;
}

void ImageProcessing::cropSection(const Mat & img, CvRect section, const string &fileName){
	return ImageProcessing::cropSection(img, section.x, section.y, section.width, section.height, fileName);
}

void ImageProcessing::cropSection(const Mat & img, int posX, int posY, int widthX, int heightY, const string &fileName){

	//Crop and save face
	Rect croppedArea(posX, posY, widthX, heightY);
	Mat croppedImg(img(croppedArea).clone());
	imwrite(directory + fName + fileName + ".jpg", croppedImg);

	namedWindow("Cropped section " + fileName, CV_WINDOW_AUTOSIZE);
	imshow("Cropped section " + fileName,croppedImg);
}

bool ImageProcessing::getTextFromImage(const Mat & img, IdentityDocument & idDoc)
{

	if (myOCR->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		return false;
	}

	tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7); // treat the image as a single text line
	myOCR->SetPageSegMode(pagesegmode);

	Mat newImg = img.clone();
	ip::Template *passportTemplate = ip::ImageProcessing::getTemplate();

	//MRZ
	//Rect text1ROI(passportTemplate->getMrz1());
	//Rect text2ROI(passportTemplate->getMrz2());

	// MRZ first and second lines position relative to top left origin
	Size sizeImg = img.size();
	int xPos = static_cast<int>(sizeImg.width * (2.0 / ID_3_PASSPORT_WIDTH));
	int yPos1 = static_cast<int>(sizeImg.height * (69.07 / ID_3_PASSPORT_HEIGHT));
	int yPos2 = static_cast<int>(sizeImg.height * (75.42 / ID_3_PASSPORT_HEIGHT));


	int width = static_cast<int>(sizeImg.width * (121.0 / ID_3_PASSPORT_WIDTH));
	int height = static_cast<int>(sizeImg.height * (6.35 / ID_3_PASSPORT_HEIGHT));

	Rect text1ROI(xPos, yPos1, width, height);
	Rect text2ROI(xPos, yPos2, width, height);

	preprocessImg(newImg, text1ROI);

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
	t1.erase(remove(t1.begin(), t1.end(), '\n'), t1.end());
	if(t1.length() != 44)	//	44 characters per line
	{
		t1 = "";
	}

	string t2(text2);
	t2.erase(remove(t2.begin(), t2.end(), '\n'), t2.end());
	if(t2.length() != 44)	//	44 characters per line
	{
		t2 = "";
	}
	splitData(idDoc, t1, t2);

	rectangle(newImg, text1ROI, Scalar(255, 255, 255), 2, 8, 0);
	rectangle(newImg, text2ROI, Scalar(255, 255, 255), 2, 8, 0);

	namedWindow("tesseract-opencv", CV_WINDOW_NORMAL);
	imshow("tesseract-opencv", newImg);
	
	//Save Data into a file
	dataToFile(idDoc);
	return true;

}

ImageProcessing::~ImageProcessing()
{

	// TODO: Commented to avoid application crash when closing it
	//delete [] text1;
	//delete [] text2;

	// destroy tesseract OCR engine
	myOCR->Clear();
	myOCR->End();
}

void ImageProcessing::splitData(IdentityDocument & passport, const string & zone1, const string & zone2)
{
	cout << "Text from image: First line: " << zone1 << endl << "Second line: " << zone2 << endl;

	string delimiter = "<<";
	string delimiter2 = "<";

	if(!zone1.empty())
	{
		//Processing Surnames and Names
		string parseFullName = zone1.substr(5,40);
		string surname = parseFullName.substr(0, parseFullName.find(delimiter));
		string name = parseFullName.erase(0, parseFullName.find(delimiter) + delimiter.length());
		//Clean delimiter in surnames
		replace(surname.begin(), surname.end(), '<', ' ');
		//Names
		size_t pos = 0;
		string token;
		while((pos = name.find(delimiter2))!= string::npos) {
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

		//Set File Name
		if(passport.getSurnames().length() || passport.getGivenNames().length())
			fName = passport.getSurnames()+ sep + passport.getGivenNames() + sep;
	}

	if(!zone2.empty())
	{
		//Zone 2
		string vId = zone2.substr(0,9);
		size_t lenghtId = vId.find('<');
		if (lenghtId!=std::string::npos)
			passport.setId(vId.substr(0,lenghtId));
		else
			passport.setId(vId);
		passport.setCheckId(zone2.substr(9,1));
		passport.setNationality(zone2.substr(10,3));
		passport.setDateBirth(zone2.substr(13,6));
		passport.setCheckBirth(zone2.substr(19,1));
		passport.setSex(zone2.substr(20,1));
		passport.setDateExpiry(zone2.substr(21,6));
		passport.setCheckExpiry(zone2.substr(27,1));
		passport.setOptionalData(zone2.substr(28,zone2.substr(28,14).find(delimiter2)));
		passport.setCheckOptional(zone2.substr(42,zone2.substr(42,1).find(delimiter2)));
		passport.setCheckOverall(zone2.substr(43,1));
	}
}

bool ImageProcessing::preprocessImg(Mat & srcImg, Rect & mrzROI)
{
	// Binary inverted threshold
	threshold(srcImg, srcImg, 152.0, 255, THRESH_BINARY_INV); //Img_13 , Img_19

	Mat tmpImg(srcImg(mrzROI).clone());
	Size sizeImg = tmpImg.size();

	std::vector<Point> points;
	Mat_<uchar>::iterator it = tmpImg.begin<uchar>();
	Mat_<uchar>::iterator end = tmpImg.end<uchar>();
	for (; it != end; ++it)
	{
		if (*it)
		{
			points.push_back(it.pos());
		}
	}

	RotatedRect box = minAreaRect(Mat(points));
	double angle = box.angle;
	if (angle < -45.)
		angle += 90.;
	Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

	cv::warpAffine(srcImg, srcImg, rot_mat, srcImg.size(), INTER_CUBIC);

	return 0;
}

void ImageProcessing::dataToFile(IdentityDocument & idDoc){
	cout << "File created: " + directory + fName + ".txt"<< endl;
	//Open Data File
	ofstream dataFile( directory + fName + ".txt");
	if (dataFile.is_open()){
		//Zone 1
		dataFile << "Type: " << idDoc.getType() << endl;
		dataFile << "Country: " << idDoc.getCountry() << endl;
		dataFile << "Surnames: " << idDoc.getSurnames() << endl;
		dataFile << "Given names: " << idDoc.getGivenNames() << endl;
		//Zone 2
		dataFile << "Id: " << idDoc.getId() << endl;
		dataFile << "CheckId: " << idDoc.getCheckId() << endl;
		dataFile << "Nationality: " << idDoc.getNationality() << endl;
		dataFile << "Birth date: " << idDoc.getDateBirth() << endl;
		dataFile << "Birth check: " << idDoc.getCheckBirth() << endl;
		dataFile << "Sex: " << idDoc.getSex() << endl;
		dataFile << "Date expiry: " << idDoc.getDateExpiry() << endl;
		dataFile << "Check expiry: " << idDoc.getCheckExpiry() << endl;
		dataFile << "Optional data: " << idDoc.getOptionalData() << endl;
		dataFile << "Check optional: " << idDoc.getCheckOptional() << endl;
		dataFile << "Check overall: " << idDoc.getCheckOverall() << endl;
		dataFile.close();
	}
	else cout << "Unable to open file";
}
