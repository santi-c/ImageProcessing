#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "opencv2/highgui/highgui.hpp"
#include "IdentityDocument.h"

namespace ip
{

class ImageProcessing{
public:
	cv::Mat detectAndCropFace(cv::Mat img);
	//void faceRecognizer(Mat img);
	//void getPersonalInformation();
	//void updateStoreFaces();
	cv::Mat cropSection(cv::Mat img, int posX, int posY, int widthX, int heightY);
	IdentityDocument splitData(string zone1, string zone2);
};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H