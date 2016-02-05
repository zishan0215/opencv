#include <opencv2/opencv.hpp>

void color_reduce(cv::Mat& image, int div=64);

int main(int argc, char **argv) {

	if (argc != 2) {
        printf("usage: ./colorreduce <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1]);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    color_reduce(image);

    cv::namedWindow("Reduced Color Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Reduced Color Image", image);

    cv::waitKey(0);
	return 0;
}

void color_reduce(cv::Mat& image, int div) {
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for(int j=0; j<nl; j++) {
		uchar* data = image.ptr<uchar>(j);
		for(int i=0; i<nc; i++) {
			data[i] = (data[i]/div)*div + div/2;
		}
	}
}