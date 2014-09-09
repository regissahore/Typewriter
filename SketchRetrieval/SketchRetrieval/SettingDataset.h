#pragma once
#include <memory>
#include "Setting.h"

class Dataset;

class SettingDataset :
    public Setting
{
public:
    SettingDataset();
    virtual ~SettingDataset();

    enum DatasetEnum
    {
        DATASET_SHOG,
    };

    DatasetEnum getDatasetEnum() const;
    void selectDatasetEnum(DatasetEnum dataset);
    std::shared_ptr<Dataset> getDataset() const;

private:
    DatasetEnum _datasetEnum;
    std::shared_ptr<Dataset> _dataset;

    virtual std::vector<double> getUniqueVector() const override final;
};

