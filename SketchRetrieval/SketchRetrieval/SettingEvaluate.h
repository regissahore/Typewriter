#pragma once
#include "Setting.h"

class SettingEvaluate
    : public Setting
{
public:
    SettingEvaluate();
    virtual ~SettingEvaluate();
    
    enum Method
    {
        METHOD_KENDALL
    };

    Method getMethod() const;
    void selectMethod(Method method);

protected:
    virtual void saveParameter(const char *filePath) const override final;
    virtual std::vector<double> getUniqueVector() const override final;

private:
    Method _method;
};

