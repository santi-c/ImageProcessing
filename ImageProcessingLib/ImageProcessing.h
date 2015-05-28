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

	bool getCustomerInfo(const string &);
	
	Template* getTemplate(){return templateType;};
	void setTemplate(Template *mTemplateType){templateType = mTemplateType;};
	string getPath(){return path;};
	void setPath(string mPath){
		path = mPath; 
		int pos1 = path.find_last_of('\\') +1;
		int pos2 = path.find_last_of('.');
		directory = path.substr(0, pos1);
		fName = path.substr(pos1, pos2-pos1);
	};

private:
	tesseract::TessBaseAPI * myOCR;
	const char * text1;
	const char * text2;

	const double ID_3_PASSPORT_HEIGHT;
	const double ID_3_PASSPORT_WIDTH;

	std::string mrzLine1;
	std::string mrzLine2;

	Template *templateType;
	string path;
	string directory;
	string fName;

	void splitData(IdentityDocument &, const string &, const string &);
	bool preprocessImg(cv::Mat &, cv::Rect &);
	void dataToFile(IdentityDocument &);

	bool detectAndCropSignature(const cv::Mat &);
	CvRect detectFace(const cv::Mat &);
	bool getTextFromImage(const cv::Mat &, IdentityDocument &);
	void cropSection(const cv::Mat & img, CvRect section, const string &fileName);
	void cropSection(const cv::Mat & img, int posX, int posY, int widthX, int heightY, const string &fileName);
};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H