#include <stdio.h>
#include <opencv2/opencv.hpp>


int main(int argc, char** argv ) {
    if ( argc != 2 ) {
        printf("usage: ./imread <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread( argv[1], 1 );

    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);

    cv::Mat result;
    cv::flip(image, result, 1);

    cv::namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output Image", result);

    cv::imwrite("../images/output.jpg", result);

    cv::waitKey(0);

    return 0;
}