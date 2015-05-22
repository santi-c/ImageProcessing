#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "opencv2/core/types_c.h"
#include "opencv2/imgproc/imgproc.hpp"

namespace ip{

class Template{

	int id;
	CvRect mrz1;
	CvRect mrz2;
	CvRect signature;
public:
	Template(cv::Mat &img, int typeId);
	~Template();
	CvRect getSignature(){return signature;};
	CvRect getMrz1(){return mrz1;};
	CvRect getMrz2(){return mrz2;};
};

}


#endif