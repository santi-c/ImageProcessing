#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "baseapi.h"
#include "opencv2/highgui/highgui.hpp"
#include "IdentityDocument.h"
#include "Template.h"

namespace ip
{

class ImageProcessing{
public:

	ImageProcessing();
	~ImageProcessing();

	CvRect detectFace(const cv::Mat &);
	//void faceRecognizer(Mat img);
	bool getTextFromImage(const cv::Mat &, IdentityDocument &);
	//void updateStoreFaces();
	void cropSection(const cv::Mat & img, CvRect section, const string &fileName);
	void cropSection(const cv::Mat & img, int posX, int posY, int widthX, int heightY, const string &fileName);
	
	Template* getTemplate(){return templateType;};
	void setTemplate(Template *mTemplateType){templateType = mTemplateType;};
	string getPath(){return path;};
	void setPath(string mPath){
		path = mPath; 
		directory = path.substr(0, path.find_last_of('\\') +1);
		fName = path.substr(path.find_last_of('\\')+1, path.find_last_of('.'));
	};

private:
	tesseract::TessBaseAPI * myOCR;
	const char * text1;
	const char * text2;
	Template *templateType;
	string path;
	string directory;
	string fName;

	void splitData(IdentityDocument &, const string &, const string &);
	bool preprocessImg(cv::Mat &, cv::Rect &);
	void dataToFile(IdentityDocument &);

	const double ID_3_PASSPORT_HEIGHT;
	const double ID_3_PASSPORT_WIDTH;

};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H