#ifndef READER
#define READER

#include <string>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageReader {
public:
    virtual Mat read(const string& imagePath) const =0;
};

#endif

