#pragma once

#include "SettingEdgeDetect.h"

class SettingControl
{
public:
    static SettingControl& getInstance();
    virtual ~SettingControl();
    SettingEdgeDetect edgeDetect;

private:
    static SettingControl *control;
    SettingControl();
};

