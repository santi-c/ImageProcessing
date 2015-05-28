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
	bool detectAndCropSignature(const cv::Mat &);
	//void faceRecognizer(Mat img);
	bool getTextFromImage(const cv::Mat &, IdentityDocument &);
	//void updateStoreFaces();
	void cropSection(const cv::Mat & img, CvRect section);
	void cropSection(const cv::Mat & img, int posX, int posY, int widthX, int heightY);
	Template* getTemplate(){return templateType;};
	void setTemplate(Template *mTemplateType){templateType = mTemplateType;};

private:
	tesseract::TessBaseAPI * myOCR;
	const char * text1;
	const char * text2;

	std::string mrzLine1;
	std::string mrzLine2;

	Template *templateType;

	void splitData(IdentityDocument &, const string &, const string &);
	bool preprocessImg(cv::Mat &, cv::Rect &);

	const double ID_3_PASSPORT_HEIGHT;
	const double ID_3_PASSPORT_WIDTH;

};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H