#include <cassert>
#include <vector>
#include <string>
#include <memory>
#include <io.h>
#include <Windows.h>
#include "Dataset.h"
#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingDetection.h"
#include "SettingFeature.h"
#include "Extractor.h"
#include "ExtractorHoG.h"
#include "FeatureExtraction.h"
using namespace std;

FeatureExtraction::FeatureExtraction()
{
}

FeatureExtraction::~FeatureExtraction()
{
}

void FeatureExtraction::extract()
{
    SettingDataset& datasetSetting = SettingControl::getInstance().dataset;
    SettingDetection& edgeSetting = SettingControl::getInstance().detect;
    SettingFeature& featureSetting = SettingControl::getInstance().feature;
    string basePath = datasetSetting.getDataset()->getBasePath();
    string sketchFolder = datasetSetting.getDataset()->getSketchFolder();
    string imageFolder = datasetSetting.getDataset()->getImageFolder();
    string edgeFolder = edgeSetting.getFolderName();
    string featureFolder = featureSetting.getFolderName();
    vector<string> categories = datasetSetting.getDataset()->getCategoryList();
    if (!CreateDirectory((featureFolder + "/" + sketchFolder).c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    if (!CreateDirectory((featureFolder + "/" + imageFolder).c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    for (auto cat : categories)
    {
        if (!CreateDirectory((featureFolder + "/" + imageFolder + "/" + cat).c_str(), NULL))
        {
            assert("Unable to create folder.");
        }
    }
    shared_ptr<Extractor> extractor;
    switch (featureSetting.getMethod())
    {
    case SettingFeature::METHOD_HOG:
        extractor = shared_ptr<Extractor>(new ExtractorHoG());
        break;
    case SettingFeature::METHOD_PHOG:
        break;
    case SettingFeature::METHOD_SHOG:
        break;
    case SettingFeature::METHOD_BHOG:
        break;
    default:
        assert("The feature extraction method is not exist.");
    }
    vector<string> sketchList = datasetSetting.getDataset()->getSketchList();
    for (auto sketch : sketchList)
    {
        string target = featureFolder + "/" + sketch;
        if (_access(target.c_str(), 0) == -1)
        {
            string source = edgeFolder + "/" + sketch;
            extractor->extract(source.c_str(), target.c_str());
        }
    }
    vector<string> imageList = datasetSetting.getDataset()->getImageList();
    for (auto image : imageList)
    {
        string target = featureFolder + "/" + image;
        if (_access(target.c_str(), 0) == -1)
        {
            string source = edgeFolder + "/" + image;
            extractor->extract(source.c_str(), target.c_str());
        }
    }
}