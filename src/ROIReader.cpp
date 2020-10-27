#include "./ROIReader.hpp"

Mat ROIReader::read(const string& imagePath) const {
    Mat m = imread(imagePath, IMREAD_GRAYSCALE);
    Rect2d r = selectROI(m);
    return m(r);
}