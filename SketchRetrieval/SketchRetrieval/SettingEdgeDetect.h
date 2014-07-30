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
            double threshold1;
            double threshold2;
            int aperture_size;
        } canny;
    };

    Method getMethod() const;
    void selectMethod(Method method);
    void setCannyParameter(double threshold1 = 50.0, double threshold2 = 200.0, int aperture_size = 3);
    Paramters getParameters() const;

protected:
    virtual std::vector<double> getUniqueVector() const override final;

private:
    Method _method;
    Paramters _parameters;
};

