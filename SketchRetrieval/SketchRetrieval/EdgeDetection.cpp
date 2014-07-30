#include <string>
#include <cassert>
#include <io.h>
#include <Windows.h>
#include "Dataset.h"
#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingDetection.h"
#include "EdgeDetection.h"
#include "Detector.h"
#include "DetectorCanny.h"
using namespace std;

EdgeDetection::EdgeDetection()
{
}


EdgeDetection::~EdgeDetection()
{
}

void EdgeDetection::detect()
{
    SettingDataset& datasetSetting = SettingControl::getInstance().dataset;
    SettingDetection& edgeSetting = SettingControl::getInstance().detect;
    string basePath = datasetSetting.getDataset()->getBasePath();
    string sketchFolder = datasetSetting.getDataset()->getSketchFolder();
    string imageFolder = datasetSetting.getDataset()->getImageFolder();
    string edgeFolder = edgeSetting.getFolderName();
    vector<string> categories = datasetSetting.getDataset()->getCategoryList();
    if (!CreateDirectory((edgeFolder + "/" + sketchFolder).c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    if (!CreateDirectory((edgeFolder + "/" + imageFolder).c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    for (auto cat : categories)
    {
        if (!CreateDirectory((edgeFolder + "/" + imageFolder + "/" + cat).c_str(), NULL))
        {
            assert("Unable to create folder.");
        }
    }
    shared_ptr<Detector> detector;
    switch (edgeSetting.getMethod())
    {
    case SettingDetection::METHOD_CANNY:
        detector = shared_ptr<Detector>(new DetectorCanny());
        break;
    default:
        assert("Edge detection method is not defined.");
    }
    vector<string> sketchList = datasetSetting.getDataset()->getSketchList();
    for (auto sketch : sketchList)
    {
        string target = edgeFolder + "/" + sketch;
        if (_access(target.c_str(), 0) == -1)
        {
            DetectorCanny canny;
            string source = basePath + sketch;
            canny.detect(source.c_str(), target.c_str());
        }
    }
    vector<string> imageList = datasetSetting.getDataset()->getImageList();
    for (auto image : imageList)
    {
        string target = edgeFolder + "/" + image;
        if (_access(target.c_str(), 0) == -1)
        {
            DetectorCanny canny;
            string source = basePath + image;
            canny.detect(source.c_str(), target.c_str());
        }
    }
}