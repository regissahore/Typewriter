#include <opencv2/opencv.hpp>
#include "CannyEdgeDetect.h"
#include "SettingControl.h"
#include "SettingEdgeDetect.h"
using namespace cv;

CannyEdgeDetect::CannyEdgeDetect()
{
}


CannyEdgeDetect::~CannyEdgeDetect()
{
}
#include <iostream>
using namespace std;
void CannyEdgeDetect::detect(const char *source, const char *target)
{
    SettingEdgeDetect setting = SettingControl::getInstance().edgeDetect;
    SettingEdgeDetect::Paramters parameter = setting.getParameters();
    double thresholdLow = parameter.canny.threshold1;
    double thresholdHigh = parameter.canny.threshold2;
    int apertureSize = parameter.canny.aperture_size;
    IplImage* srcImage = cvLoadImage(source, 0);
    cout << source << endl;
    cout << target << endl;
    CvSize size = cvSize(srcImage->width, srcImage->height);
    IplImage* tarImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
    cvCanny(srcImage, tarImage, thresholdLow, thresholdHigh, apertureSize);
    cvSaveImage(target, tarImage);
    cvReleaseImage(&srcImage);
    cvReleaseImage(&tarImage);
}