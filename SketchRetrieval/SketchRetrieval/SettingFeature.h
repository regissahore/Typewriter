#pragma once
#include "Setting.h"
class SettingFeature :
    public Setting
{
public:
    SettingFeature();
    virtual ~SettingFeature();

    enum Method
    {
        METHOD_HOG,
        METHOD_PHOG,
        METHOD_SHOG,
        METHOD_BHOG,
    };

    union Parameter
    {
        struct
        {
            int windowW, windowH;
            int blockW, blockH;
            int cellW, cellH;
            int shiftW, shiftH;
            int nBins;
        } hog;
    };

    Method getMethod() const;
    void selectMethod(Method method);
    Parameter getParameter() const;    
    void setHoGParameter(int windowW = 640, int windowH = 640,
                         int blockW = 64, int blockH = 64,
                         int cellW = 32, int cellH = 32,
                         int shiftW = 32, int shiftH = 32,
                         int nBins = 9);

protected:
    virtual void saveParameter(const char *filePath) const override final;
    virtual std::vector<double> getUniqueVector() const override final;

private:
    Method _method;
    Parameter _parameter;
};

