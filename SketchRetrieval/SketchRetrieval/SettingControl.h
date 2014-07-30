#pragma once

#include "SettingDataset.h"
#include "SettingDetection.h"
#include "SettingFeature.h"
#include "SettingRanking.h"

class SettingControl
{
public:
    static SettingControl& getInstance();
    virtual ~SettingControl();

    SettingDataset dataset;
    SettingDetection detect;
    SettingFeature feature;
    SettingRanking ranking;

private:
    static SettingControl *control;
    SettingControl();
};

