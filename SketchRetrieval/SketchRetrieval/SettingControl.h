#pragma once

#include "SettingDataset.h"
#include "SettingEdgeDetect.h"
#include "SettingFeature.h"

class SettingControl
{
public:
    static SettingControl& getInstance();
    virtual ~SettingControl();

    SettingDataset dataset;
    SettingEdgeDetect edgeDetect;
    SettingFeature feature;

private:
    static SettingControl *control;
    SettingControl();
};

