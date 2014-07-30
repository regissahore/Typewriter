#pragma once

#include "SettingDataset.h"
#include "SettingEdgeDetect.h"

class SettingControl
{
public:
    static SettingControl& getInstance();
    virtual ~SettingControl();

    SettingDataset dataset;
    SettingEdgeDetect edgeDetect;

private:
    static SettingControl *control;
    SettingControl();
};

