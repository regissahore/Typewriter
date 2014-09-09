#include <fstream>
#include <cassert>
#include "SettingControl.h"
#include "SettingRanking.h"
#include "SettingEvaluate.h"
using namespace std;

SettingEvaluate::SettingEvaluate()
{
    this->_settingName = "Evalute";
    this->selectMethod(METHOD_KENDALL);
}

SettingEvaluate::~SettingEvaluate()
{
}

SettingEvaluate::Method SettingEvaluate::getMethod() const
{
    return this->_method;
}

void SettingEvaluate::selectMethod(SettingEvaluate::Method method)
{
    this->_method = method;
}

void SettingEvaluate::saveParameter(const char *filePath) const
{
    fstream fout;
    fout.open(filePath, ios::out);
    fout << "Ranking: " << SettingControl::getInstance().ranking.getUniqueString() << endl;
    fout << "Method: ";
    switch (this->_method)
    {
    case METHOD_KENDALL:
        fout << "Kendall";
        break;
    default:
        assert("The evaluation method is not exist.");
    }
    fout << endl;
    fout.flush();
    fout.close();
}

vector<double> SettingEvaluate::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back((double)SettingControl::getInstance().ranking.getUniqueNumber());
    unique.push_back(this->_method);
    return unique;
}