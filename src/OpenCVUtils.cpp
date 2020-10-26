#include <opencv4/opencv2/opencv.hpp>

#include <string>

using namespace cv;

void imageManipulations() {
    const std::string STRAIGHT_IMAGE_PATH = "datasets/hill-rgb-0007.png";
    const std::string ROTATED_IMAGE_PATH = "datasets/hill-ir-rot-0007.png";
    const std::string OUTPUT_KEYPOINTS_PATH = "datasets/matching-keypoints.jpg";
    const std::string OUTPUT_ALIGNED_ROTATED_PATH = "datasets/hill-rgb-0007-aligned.png";
    const std::string OUTPUT_ALIGNED_STRAIGHT_PATH = "datasets/hill-ir-rot-0007-aligned.png";

    Mat straightImage = imread(STRAIGHT_IMAGE_PATH, IMREAD_GRAYSCALE);
    Mat rotatedImage = imread(ROTATED_IMAGE_PATH, IMREAD_GRAYSCALE);

    Rect2d r = selectROI(straightImage);
    Mat croppedStraightImage = straightImage(r);
    r = selectROI(rotatedImage);
    Mat croppedRotatedImage = rotatedImage(r);

    const int MAX_FEATURES = 5000;
    const float GOOD_MATCH_PERCENT = 0.05f;

    // Use variable aliases for the next section
    // We want to align an image using a certain reference
    Mat imageR = croppedStraightImage; // Reference Image
    Mat imageT = croppedRotatedImage; // Transformed Image

    std::vector<KeyPoint> keypointsR, keypointsT;
    Mat descriptorsR, descriptorsT;

    std:Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
    orb->detectAndCompute(imageT, Mat(), keypointsT, descriptorsT);
    orb->detectAndCompute(imageR, Mat(), keypointsR, descriptorsR);

    std::vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(descriptorsT, descriptorsR, matches, Mat());

    std::sort(matches.begin(), matches.end());

    const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
    matches.erase(matches.begin() + numGoodMatches, matches.end());

    Mat imMatches;
    drawMatches(imageT, keypointsT,imageR, keypointsR, matches, imMatches);
    imwrite(OUTPUT_KEYPOINTS_PATH, imMatches);

    std::vector<Point2f> pointsT, pointsR;

    for( size_t i = 0; i < matches.size(); i++) {
        pointsT.push_back(keypointsT[matches[i].queryIdx].pt);
        pointsR.push_back(keypointsR[matches[i].trainIdx].pt);
    }

    Mat homography = findHomography(pointsT, pointsR, RANSAC);

    Mat alignedImage;
    warpPerspective(imageT, alignedImage, homography, imageR.size());
    imwrite(OUTPUT_ALIGNED_ROTATED_PATH, alignedImage);
    imwrite(OUTPUT_ALIGNED_STRAIGHT_PATH, imageR);

    waitKey(0);

}