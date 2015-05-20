#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "baseapi.h"
#include "opencv2/highgui/highgui.hpp"
#include "IdentityDocument.h"

namespace ip
{

class ImageProcessing{
public:

	ImageProcessing();
	~ImageProcessing();

	void detectAndCropFace(cv::Mat & img);
	//void faceRecognizer(Mat img);
	bool getTextFromImage(cv::Mat & img, std::string & firstLine, std::string & secondLine);
	//void updateStoreFaces();
	cv::Mat cropSection(cv::Mat img, int posX, int posY, int widthX, int heightY);
	IdentityDocument splitData(string zone1, string zone2);

private:
	tesseract::TessBaseAPI * myOCR;
	const char * text1;
	const char * text2;

};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H