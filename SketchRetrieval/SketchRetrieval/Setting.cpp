#include <Windows.h>
#include <cassert>
#include "Setting.h"
using namespace std;

Setting::Setting()
{
}


Setting::~Setting()
{
}

string Setting::getFolderName() const
{
    string setting;
    vector<double> unqiue = getUniqueVector();
    for (auto variable : unqiue)
    {
        setting = setting + to_string(variable) + " ";
    }
    string folderName = this->_settingName + "/" + ull2hex(BKDRHash(setting));
    if (!CreateDirectory(this->_settingName.c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    if (!CreateDirectory(folderName.c_str(), NULL))
    {
        assert("Unable to create folder.");
    }
    return folderName;
}

vector<double> Setting::getUniqueVector() const
{
    return vector<double>();
}

unsigned long long Setting::BKDRHash(std::string setting) const
{
    unsigned long long seed = 13131;
    unsigned long long hash = 0;
    for (auto ch : setting)
    {
        hash = hash * seed + ch;
    }
    return hash;
}

char Setting::digit2hex(int value) const
{
    if (value < 10)
    {
        return '0' + value;
    }
    return 'A' + value - 10;
}

string Setting::ull2hex(unsigned long long value) const
{
    string hex;
    for (int i = 0; i < 16; ++i)
    {
        hex += digit2hex(value & ((1LL << 4) - 1));
        value >>= 4;
    }
    return hex;
}