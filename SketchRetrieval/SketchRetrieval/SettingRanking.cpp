#include <vector>
#include <fstream>
#include <cassert>
#include "SettingControl.h"
#include "SettingFeature.h"
#include "SettingRanking.h"
using namespace std;

SettingRanking::SettingRanking()
{
    this->_settingName = "Ranking";
    this->selectMethod(METHOD_EUCILID);
}

SettingRanking::~SettingRanking()
{
}

SettingRanking::Method SettingRanking::getMethod() const
{
    return this->_method;
}

void SettingRanking::selectMethod(SettingRanking::Method method)
{
    this->_method = method;
}

void SettingRanking::saveParameter(const char *filePath) const
{
    fstream fout;
    fout.open(filePath, ios::out);
    fout << "Feature: " << SettingControl::getInstance().feature.getUniqueString() << endl;
    switch (this->_method)
    {
    case METHOD_EUCILID:
        fout << "Method: Eucilid" << endl;
    default:
        assert("Ranking method does not exist.");
    }
    fout.flush();
    fout.close();
}

vector<double> SettingRanking::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back(SettingControl::getInstance().feature.getUniqueNumber());
    unique.push_back(this->_method);
    return unique;
}