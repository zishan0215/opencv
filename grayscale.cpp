#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
	if (argc != 2) {
        std::cout<<"usage: ./imread <Image_Path>"<<std::endl;
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1]);

    if (!image.data) {
        std::cout<<"No image data"<<std::endl;
        return -1;
    }

	cv::Mat gray_image;
	
	cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
	
	cv::imwrite("../images/Gray_Image.jpg", gray_image);
	
	cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Gray image", cv::WINDOW_AUTOSIZE);
	
	cv::imshow("Original image", image);
	cv::imshow("Gray image", gray_image);
	
	cv::waitKey(0);
	
	return 0;
}
