#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "opencv2/highgui/highgui.hpp"

namespace ip
{

class ImageProcessing{
public:
	void detectAndCropFace(cv::Mat img);
	//void faceRecognizer(Mat img);
	//void getPersonalInformation();
	//void updateStoreFaces();
	void cropSection(cv::Mat img, int posX, int posY, int widthX, int heightY);

};

}	// Namespace ip
#endif	// IMAGE_PROCESSING_H