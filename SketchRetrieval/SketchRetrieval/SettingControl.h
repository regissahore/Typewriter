#pragma once

#include "SettingDataset.h"
#include "SettingDetection.h"
#include "SettingFeature.h"
#include "SettingRanking.h"
#include "SettingEvaluate.h"

class SettingControl
{
public:
    static SettingControl& getInstance();
    virtual ~SettingControl();

    SettingDataset dataset;
    SettingDetection detect;
    SettingFeature feature;
    SettingRanking ranking;
    SettingEvaluate evaluate;

    void finishExperiment();

private:
    static SettingControl *control;
    SettingControl();

    void readAndPrint(std::string inputPath, std::string outputPath);
};

