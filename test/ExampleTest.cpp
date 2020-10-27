#include <gtest/gtest.h>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <cstdio>

#include "../src/ImageReader.hpp"
#include "../src/ImageAlign.hpp"

using namespace cv;
using namespace std;

class TestReader: public ImageReader {
public:
    Mat read(const string& imagePath) const {
        return imread(imagePath, IMREAD_GRAYSCALE);
    };
};

ImageAlign* buildImageAlign() {
    return new ImageAlign(new TestReader());
}

bool checkAndDeleteFile(char path[]) {
    return remove(path) == 0;
};

TEST(ManipulationsTest, VerifyProperFilesAreGenerated) {
    ImageAlign* imageAlign = buildImageAlign();
    string TRANSFORMED_IMAGE_PATH = "./datasets/hill-ir-rot-0007.png";
    string REFERENCE_IMAGE_PATH = "./datasets/hill-rgb-0007.png";

    imageAlign->align(TRANSFORMED_IMAGE_PATH, REFERENCE_IMAGE_PATH);
    char GENERATED_KEYPOINTS_PATH[] = "./datasets/matching-keypoints.jpg";
    char GENERATED_REFERENCE_ALIGNED_PATH[] = "./datasets/hill-ir-rot-0007-aligned.png";
    char GENERATED_TRANSFORMED_ALIGNED_PATH[] = "./datasets/hill-rgb-0007-aligned.png";

    EXPECT_TRUE(checkAndDeleteFile(GENERATED_KEYPOINTS_PATH));
    EXPECT_TRUE(checkAndDeleteFile(GENERATED_REFERENCE_ALIGNED_PATH));
    EXPECT_TRUE(checkAndDeleteFile(GENERATED_TRANSFORMED_ALIGNED_PATH));

    delete imageAlign;
}
