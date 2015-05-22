#include "Template.h"


ip::Template::Template(cv::Mat &img, int typeId){

	switch (typeId)
	{
		case 1://Indian Passport
			signature.x =  static_cast<int>(img.cols * (6.0 / 100.0));
			signature.y = static_cast<int>(img.rows * (55.0 / 100.0));
			signature.width = static_cast<int>(img.cols * (38.0 / 100.0));
			signature.height = static_cast<int>(img.rows * (20.0 / 100.0));

			mrz1.x = static_cast<int>(img.cols * (2.0 / 100.0));
			mrz1.y = static_cast<int>(img.rows * (80.0 / 100.0));
			mrz1.width = static_cast<int>(img.cols * (93.0 / 100.0));
			mrz1.height = static_cast<int>(img.rows * (7.0 / 100.0));

			mrz2.x = static_cast<int>(img.cols * (2.0 / 100.0));
			mrz2.y = static_cast<int>(img.rows * (87.0 / 100.0));
			mrz2.width = static_cast<int>(img.cols * (93.0 / 100.0));
			mrz2.height = static_cast<int>(img.rows * (7.0 / 100.0));
			break;
		default://USA Passport
			signature.x =  static_cast<int>(img.cols * (12.0 / 100.0));
			signature.y = static_cast<int>(img.rows * (38.0 / 100.0));
			signature.width = static_cast<int>(img.cols * (75.0 / 100.0));
			signature.height = static_cast<int>(img.rows * (12.0 / 100.0));

			mrz1.x = static_cast<int>(img.cols * (2.0 / 100.0));
			mrz1.y = static_cast<int>(img.rows * (91.0 / 100.0));
			mrz1.width = static_cast<int>(img.cols * (93.0 / 100.0));
			mrz1.height = static_cast<int>(img.rows * (4.0 / 100.0));

			mrz2.x = static_cast<int>(img.cols * (2.0 / 100.0));
			mrz2.y = static_cast<int>(img.rows * (95.0 / 100.0));
			mrz2.width = static_cast<int>(img.cols * (93.0 / 100.0));
			mrz2.height = static_cast<int>(img.rows * (4.0 / 100.0));
			break;
	}
}