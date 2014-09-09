#pragma once
#include "Setting.h"

class SettingRanking :
    public Setting
{
public:
    SettingRanking();
    virtual ~SettingRanking();

    enum Method
    {
        METHOD_EUCILID,
    };
    
    Method getMethod() const;
    void selectMethod(Method method);

protected:
    virtual void saveParameter(const char *filePath) const override final;
    virtual std::vector<double> getUniqueVector() const override final;

private:
    Method _method;
};

