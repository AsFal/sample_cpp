#include "./ImageAlign.hpp"

ImageAlign::ImageAlign(ImageReader * reader) {
    imageReader_ = reader;
}

void ImageAlign::align(const string& transformedImagePath, const string& referenceImagePath) const {
    Mat transformedMat = imageReader_->read(transformedImagePath);
    Mat referenceMat = imageReader_->read(referenceImagePath);
    Mat alignedMat;
    Mat keypointsMat;

    alignMatrices(transformedMat, referenceMat, alignedMat, keypointsMat);

    imwrite(getParentDir(transformedImagePath) + "/matching-keypoints.jpg", keypointsMat);
    imwrite(addAlignedSuffix(transformedImagePath), transformedMat);
    imwrite(addAlignedSuffix(referenceImagePath), referenceMat);
}


void ImageAlign::alignMatrices(const Mat &transformedMat, const Mat &referenceMat, Mat &alignedMat, Mat &keypointMat) const {
    const int MAX_FEATURES = 5000;
    const float GOOD_MATCH_PERCENT = 0.05f;

    vector<KeyPoint> keypointsR, keypointsT;
    Mat descriptorsR, descriptorsT;

    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
    orb->detectAndCompute(transformedMat, Mat(), keypointsT, descriptorsT);
    orb->detectAndCompute(referenceMat, Mat(), keypointsR, descriptorsR);

    vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(descriptorsT, descriptorsR, matches, Mat());

    sort(matches.begin(), matches.end());

    const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
    matches.erase(matches.begin() + numGoodMatches, matches.end());

    drawMatches(transformedMat, keypointsT,referenceMat, keypointsR, matches, keypointMat);

    vector<Point2f> pointsT, pointsR;

    for( size_t i = 0; i < matches.size(); i++) {
        pointsT.push_back(keypointsT[matches[i].queryIdx].pt);
        pointsR.push_back(keypointsR[matches[i].trainIdx].pt);
    }

    Mat homography = findHomography(pointsT, pointsR, RANSAC);

    warpPerspective(transformedMat, alignedMat, homography, referenceMat.size());
}

string ImageAlign::addAlignedSuffix(string path) const {
    return path.insert(path.length() - 4, "-aligned");
}

string  ImageAlign::getParentDir(const string& str) const {
    return str.substr(0,str.find_last_of('/'));
}