#include <iostream>
#include <opencv2/opencv.hpp>

void sharpen(const cv::Mat&, cv::Mat&);
void sharpen2D(const cv::Mat&, cv::Mat&);

int main(int argc, char **argv) {

	if (argc != 2) {
        printf("usage: ./sharpen <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], 0);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    cv::Mat duplicate;

    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Original Image", image);

    sharpen(image, duplicate);

    cv::namedWindow("Sharpened Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Sharpened Image", duplicate);

    image = cv::imread(argv[1], 0);
    sharpen2D(image, duplicate);

    cv::namedWindow("Sharpened Image kernel", cv::WINDOW_AUTOSIZE );
    cv::imshow("Sharpened Image kernel", duplicate);

    cv::waitKey(0);
	return 0;

}

void sharpen(const cv::Mat& image, cv::Mat& result) {
	
	result.create(image.size(), image.type());

	int nr = image.rows;
	int nc = image.cols;

	for(int j=1; j<nr-1; j++) {
		const uchar* previous = image.ptr<uchar>(j-1);
		const uchar* current = image.ptr<uchar>(j);
		const uchar* next = image.ptr<uchar>(j+1);

		uchar* output = result.ptr<uchar>(j);

		for(int i=1; i<nc-1; i++) {
			*output = cv::saturate_cast<uchar>(5*current[i] - current[i-1] - current[i+1] - previous[i] - next[i]);
			output++;			
		}
	}

	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols-1).setTo(cv::Scalar(0)); 

}

void sharpen2D(const cv::Mat &image, cv::Mat &result) {

	// Construct kernel (all entries initialized to 0)
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	// assigns kernel values
	kernel.at<float>(1,1)= 5.0;
	kernel.at<float>(0,1)= -1.0;
	kernel.at<float>(2,1)= -1.0;
	kernel.at<float>(1,0)= -1.0;
	kernel.at<float>(1,2)= -1.0;

	//filter the image
	cv::filter2D(image,result,image.depth(),kernel);

}
