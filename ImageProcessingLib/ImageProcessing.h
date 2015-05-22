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

	void detectAndCropFace(const cv::Mat &);
	//void faceRecognizer(Mat img);
	bool getTextFromImage(const cv::Mat &, IdentityDocument &);
	//void updateStoreFaces();
	void cropSection(cv::Mat & img, CvRect section);
	void cropSection(cv::Mat & img, int posX, int posY, int widthX, int heightY);
	Template* getTemplate(){return templateType;};
	void setTemplate(Template *mTemplateType){templateType = mTemplateType;};

private:
	tesseract::TessBaseAPI * myOCR;
	const char * text1;
	const char * text2;
	Template *templateType;

	void splitData(IdentityDocument &, const string &, const string &);
	bool preprocessImg(cv::Mat &, cv::Rect &);

};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H