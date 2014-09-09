#include <opencv2/opencv.hpp>
#include "DetectorCanny.h"
#include "SettingControl.h"
#include "SettingDetection.h"
using namespace cv;

DetectorCanny::DetectorCanny()
{
}


DetectorCanny::~DetectorCanny()
{
}

void DetectorCanny::detect(const char *srcPath, const char *dstPath)
{
    SettingDetection setting = SettingControl::getInstance().detect;
    SettingDetection::Paramters parameter = setting.getParameters();
    int windowW = parameter.canny.windowW;
    int windowH = parameter.canny.windowH;
    double thresholdLow = parameter.canny.thresholdLow;
    double thresholdHigh = parameter.canny.thresholdHigh;
    int apertureSize = parameter.canny.apertureSize;
    IplImage* srcImage = cvLoadImage(srcPath, 0);
    IplImage* resizeImage = cvCreateImage(cvSize(windowW, windowH), srcImage->depth, srcImage->nChannels);
    cvResize(srcImage, resizeImage);
    IplImage* tarImage = cvCreateImage(cvSize(windowW, windowH), IPL_DEPTH_8U, 1);
    cvCanny(resizeImage, tarImage, thresholdLow, thresholdHigh, apertureSize);
    cvSaveImage(dstPath, tarImage);
    cvReleaseImage(&srcImage);
    cvReleaseImage(&resizeImage);
    cvReleaseImage(&tarImage);
}