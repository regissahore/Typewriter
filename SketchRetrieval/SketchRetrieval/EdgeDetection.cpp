#include <string>
#include <cassert>
#include <io.h>
#include <Windows.h>
#include "Dataset.h"
#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingEdgeDetect.h"
#include "EdgeDetection.h"
#include "CannyEdgeDetect.h"
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
    SettingEdgeDetect& edgeSetting = SettingControl::getInstance().edgeDetect;
    string basePath = datasetSetting.getDataset()->getBasePath();
    string imageFolder = datasetSetting.getDataset()->getImageFolder();
    string edgeFolder = edgeSetting.getFolderName();
    vector<string> categories = datasetSetting.getDataset()->getCategoryList();
    for (auto cat : categories)
    {
        if (!CreateDirectory((edgeFolder + "/" + cat).c_str(), NULL))
        {
            assert("Unable to create folder.");
        }
    }
    vector<string> imageList = datasetSetting.getDataset()->getImageList();
    switch (edgeSetting.getMethod())
    {
    case SettingEdgeDetect::METHOD_CANNY:
        for (auto image : imageList)
        {
            string target = edgeFolder + "/" + image;
            if ((_access(target.c_str(), 0)) == -1)
            {
                CannyEdgeDetect canny;
                string source = basePath + imageFolder + image;
                canny.detect(source.c_str(), target.c_str());
            }
        }
        break;
    default:
        assert("Edge detection method is not defined.");
    }
}