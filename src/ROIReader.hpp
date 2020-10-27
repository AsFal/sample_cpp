
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include "./ImageReader.hpp"

class ROIReader: public ImageReader {
public:
    Mat read(const string& imagePath) const override;
};

class something {

};
