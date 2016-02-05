#include <opencv2/opencv.hpp>

void salt(cv::Mat&, int);

int main(int argc, char **argv) {
	cv::Mat image;
	image = cv::imread(argv[1]);

	salt(image, 3000);
	cv::namedWindow("Salt and Pepper Image");
	cv::imshow("Salt and Pepper Image", image);

	cv::waitKey(0);

	return 0;
}

void salt(cv::Mat &image, int n) {
	for(int k=0; k<n; k++) {
		int i = rand()%image.cols;
		int j = rand()%image.rows;

		if(image.channels() == 1) {			// gray level image
			image.at<uchar>(j, i) = 255;	// white
		} else if(image.channels() == 3) {	// color image
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}