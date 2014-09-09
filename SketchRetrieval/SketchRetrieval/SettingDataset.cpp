#include <cassert>
#include "SettingDataset.h"
#include "DatasetSHoG.h"
using namespace std;

SettingDataset::SettingDataset()
{
    this->selectDatasetEnum(DATASET_SHOG);
}

SettingDataset::~SettingDataset()
{
}

SettingDataset::DatasetEnum SettingDataset::getDatasetEnum() const
{
    return this->_datasetEnum;
}

shared_ptr<Dataset> SettingDataset::getDataset() const
{
    return this->_dataset;
}

void SettingDataset::selectDatasetEnum(SettingDataset::DatasetEnum dataset)
{
    this->_datasetEnum = dataset;
    switch (dataset)
    {
    case DATASET_SHOG:
        this->_dataset = shared_ptr<Dataset>(new DatasetSHoG());
        break;
    default:
        assert("No such dataset.");
    }
}

vector<double> SettingDataset::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back(this->_datasetEnum);
    return unique;
}