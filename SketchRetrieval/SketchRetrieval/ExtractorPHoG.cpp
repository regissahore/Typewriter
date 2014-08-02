#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "SettingControl.h"
#include "SettingFeature.h"
#include "ExtractorPHoG.h"
using namespace std;
using namespace cv;

ExtractorPHoG::ExtractorPHoG()
{
}

ExtractorPHoG::~ExtractorPHoG()
{
}

void ExtractorPHoG::extract(const char *srcPath, const char *dstPath)
{
    SettingFeature setting = SettingControl::getInstance().feature;
    SettingFeature::Parameter parameter = setting.getParameter();
    int windowW = parameter.pHog.windowW;
    int windowH = parameter.pHog.windowH;
    int nBins = parameter.pHog.nBins;
    int layer = parameter.pHog.layer;
    IplImage* srcImage = cvLoadImage(srcPath, 0);
    IplImage* resizeImage = cvCreateImage(cvSize(windowW, windowH), srcImage->depth, srcImage->nChannels);
    cvResize(srcImage, resizeImage);
    HOGDescriptor hog(cvSize(windowW, windowH), cvSize(windowW, windowH), cvSize(windowW, windowH), cvSize(windowW, windowH), nBins);
    vector<float> descriptors;
    hog.compute(resizeImage, descriptors);
    vector<float> subDescritor;
    for (int l = 1; l < layer; ++l)
    {
        int subNum = 1 << l;
        int subW = windowW / subNum;
        int subH = windowH / subNum;
        IplImage* subImage = cvCreateImage(cvSize(subW, subH), srcImage->depth, srcImage->nChannels);
        hog = HOGDescriptor(cvSize(subW, subH), cvSize(subW, subH), cvSize(subW, subH), cvSize(subW, subH), nBins);
        for (int x = 0; x < subNum; ++x)
        {
            for (int y = 0; y < subNum; ++y)
            {
                cvSetImageROI(resizeImage, cvRect(x * subW, y * subH, subW, subH));
                cvCopy(resizeImage, subImage, NULL);
                cvResetImageROI(resizeImage);
                hog.compute(subImage, subDescritor);
                for (auto value : subDescritor)
                {
                    descriptors.push_back(value / subNum);
                }
            }
        }
        cvReleaseImage(&subImage);
    }
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