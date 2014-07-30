#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "SettingControl.h"
#include "SettingFeature.h"
#include "ExtractorHoG.h"
using namespace std;
using namespace cv;

ExtractorHoG::ExtractorHoG()
{
}

ExtractorHoG::~ExtractorHoG()
{
}

void ExtractorHoG::extract(const char *srcPath, const char *dstPath)
{
    SettingFeature setting = SettingControl::getInstance().feature;
    SettingFeature::Parameter parameter = setting.getParameter();
    int windowW = parameter.hog.windowW;
    int windowH = parameter.hog.windowH;
    int blockW = parameter.hog.blockW;
    int blockH = parameter.hog.blockH;
    int shiftW = parameter.hog.shiftW;
    int shiftH = parameter.hog.shiftH;
    int cellW = parameter.hog.cellW;
    int cellH = parameter.hog.cellH;
    int nBins = parameter.hog.nBins;
    IplImage* srcImage = cvLoadImage(srcPath, 0);
    IplImage* resizeImage = cvCreateImage(cvSize(windowW, windowH), srcImage->depth, srcImage->nChannels);
    cvResize(srcImage, resizeImage);
    HOGDescriptor hog (cvSize(windowW, windowH), cvSize(blockW, blockH), cvSize(shiftW, shiftH), cvSize(cellW, cellH), nBins);
    vector<float> descriptors;
    hog.compute(resizeImage, descriptors, Size(0, 0), Size(0, 0));
    cvReleaseImage(&srcImage);
    cvReleaseImage(&resizeImage);
    fstream fout;
    fout.open(dstPath, ios::out);
    int cnt = 0;
    for (auto value : descriptors)
    {
        fout << value << " ";
        if (++cnt % nBins == 0)
        {
            fout << endl;
        }
    }
    fout.flush();
    fout.close();
}