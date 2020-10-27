#include "./ROIReader.hpp"

Mat ROIReader::read(string imagePath) const {
    Mat m = imread(imagePath, IMREAD_GRAYSCALE);
    Rect2d r = selectROI(m);
    return m(r);
}