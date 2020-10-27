#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "src/ROIReader.hpp"
#include "src/ImageAlign.hpp"

using namespace cv;

int main(int argc, char** argv )
{
    string TRANSFORMED_IMAGE_PATH = "./datasets/hill-ir-rot-0007.png";
    string REFERENCE_IMAGE_PATH = "./datasets/hill-rgb-0007.png";

    ROIReader* reader = new ROIReader();
    ImageAlign imageAlign(reader);
    imageAlign.align(TRANSFORMED_IMAGE_PATH, REFERENCE_IMAGE_PATH);

    return 0;
}