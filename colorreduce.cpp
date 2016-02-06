#include <opencv2/opencv.hpp>

void color_reduce(cv::Mat& image, int div=64);
void color_reduce_itertor(cv::Mat& image, int div=64);

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

    cv::Mat duplicate = image.clone();

    color_reduce(image);

    cv::namedWindow("Reduced Color Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Reduced Color Image", image);

    color_reduce(duplicate);

    cv::namedWindow("Reduced Color Duplicate Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Reduced Color Duplicate Image", duplicate);


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

void color_reduce_itertor(cv::Mat& image, int div) {
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator it_end = image.end<cv::Vec3b>();

	for(; it != it_end; it++) {
		(*it)[0] = ((*it)[0]/div)*div + div/2;
		(*it)[1] = ((*it)[1]/div)*div + div/2;
		(*it)[2] = ((*it)[2]/div)*div + div/2;
	}
}