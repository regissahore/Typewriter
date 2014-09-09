#include <string>
#include <memory>
#include <cassert>
#include <io.h>
#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingFeature.h"
#include "SettingRanking.h"
#include "Dataset.h"
#include "Ranking.h"
#include "RankingEucilid.h"
#include "DistanceRanking.h"
using namespace std;

DistanceRanking::DistanceRanking()
{
}

DistanceRanking::~DistanceRanking()
{
}

void DistanceRanking::ranking()
{
    SettingDataset& datasetSetting = SettingControl::getInstance().dataset;
    SettingFeature& featureSetting = SettingControl::getInstance().feature;
    SettingRanking& rankingSetting = SettingControl::getInstance().ranking;
    shared_ptr<Dataset> dataset = datasetSetting.getDataset();
    string sketchFolder = dataset->getSketchFolder();
    string imageFolder = dataset->getImageFolder();
    string featureFolder = featureSetting.getFolderName();
    string rankingFolder = rankingSetting.getFolderName();
    vector<string> categories = dataset->getCategoryList();
    shared_ptr<Ranking> ranking;
    switch (rankingSetting.getMethod())
    {
    case SettingRanking::METHOD_EUCILID:
        ranking = shared_ptr<Ranking>(new RankingEucilid());
        break;
    default:
        assert("Ranking method is not defined.");
    }
    for (auto cat : categories)
    {
        string resultPath = rankingFolder + cat;
        if (_access(resultPath.c_str(), 0) == -1)
        {
            string sketchPath = featureFolder + dataset->getSketch(cat);
            vector<string> imagePath = dataset->getImageList(cat);
            for (unsigned int i = 0; i < imagePath.size(); ++i)
            {
                imagePath[i] = featureFolder + imagePath[i];
            }
            vector<string> imageName = dataset->getImageNames(cat);
            ranking->ranking(sketchPath, imagePath, imageName, resultPath);
        }
    }
}