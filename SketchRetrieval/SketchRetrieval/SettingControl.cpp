#include "SettingControl.h"

SettingControl *SettingControl::control = nullptr;

SettingControl::SettingControl()
{
}


SettingControl::~SettingControl()
{
}

SettingControl& SettingControl::getInstance()
{
    if (nullptr == SettingControl::control)
    {
        SettingControl::control = new SettingControl();
    }
    return *SettingControl::control;
}