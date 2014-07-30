#pragma once

#include <vector>
#include <string>

class Setting
{
public:
    Setting();
    virtual ~Setting();
    std::string getFolderName() const;
    unsigned long long getUniqueNumber() const;

protected:
    std::string _settingName;

    virtual void saveParameter(const char *filePath) const;
    virtual std::vector<double> getUniqueVector() const;

private:
    unsigned long long BKDRHash(std::string setting) const;
    char digit2hex(int value) const;
    std::string ull2hex(unsigned long long value) const;
};

