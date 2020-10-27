#ifndef ROI_READER
#define ROI_READER

#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include "./ImageReader.hpp"

using namespace std;
using namespace cv;

class ImageAlign {
public:
    ImageAlign(ImageReader*);
    void align (const string& transformedImagePath, const string& referenceImagePath) const;
private:
    const ImageReader* imageReader_;
    void alignMatrices(
            const Mat& transformed,
            const Mat& reference,
            Mat& aligned,
            Mat& keypoint
            ) const;
    string addAlignedSuffix(string) const;
    string getParentDir(const string&) const;
};

#endif