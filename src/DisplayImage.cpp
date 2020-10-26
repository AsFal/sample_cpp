#include <opencv4/opencv2/opencv.hpp>

void display(char* path) {
    cv::Mat image;
    image = cv::imread( path, 1 );
    if (!image.data) {
        throw "No image data \n";
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    imshow("Display Image", image);
}
