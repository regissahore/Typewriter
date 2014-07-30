#pragma once

#include <vector>
#include <string>

class Setting
{
public:
    Setting();
    virtual ~Setting();
    std::string getFolderName() const;

protected:
    virtual std::vector<double> getUniqueVector() const;
    std::string _settingName;

private:
    unsigned long long BKDRHash(std::string setting) const;
    char digit2hex(int value) const;
    std::string ull2hex(unsigned long long value) const;
};

