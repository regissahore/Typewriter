#pragma once
#include "Setting.h"

class SettingEdgeDetect :
    public Setting
{
public:
    SettingEdgeDetect();
    virtual ~SettingEdgeDetect();

    enum Method
    {
        METHOD_CANNY,
    };
    union Paramters
    {
        struct 
        {
            int windowW, windowH;
            double thresholdLow;
            double thresholdHigh;
            int apertureSize;
        } canny;
    };

    Method getMethod() const;
    void selectMethod(Method method);
    void setCannyParameter(int windowW = 640, int windowH = 640, double thresholdLow = 50.0, double thresholdHigh = 200.0, int apertureSize = 3);
    Paramters getParameters() const;

protected:
    virtual void saveParameter(const char *filePath) const override final;
    virtual std::vector<double> getUniqueVector() const override final;

private:
    Method _method;
    Paramters _parameters;
};

