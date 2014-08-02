#include <fstream>
#include <cassert>
#include "SettingControl.h"
#include "SettingDetection.h"
#include "SettingFeature.h"
using namespace std;

SettingFeature::SettingFeature()
{
    this->_settingName = "Feature";
    this->selectMethod(METHOD_HOG);
}

SettingFeature::~SettingFeature()
{
}

SettingFeature::Method SettingFeature::getMethod() const
{
    return this->_method;
}

void SettingFeature::selectMethod(SettingFeature::Method method)
{
    this->_method = method;
    switch (method)
    {
    case METHOD_HOG:
        this->setHoGParameter();
        break;
    case METHOD_PHOG:
        this->setPHoGParameter();
        break;
    case METHOD_SHOG:
        break;
    case METHOD_BHOG:
        break;
    default:
        assert("Undefined feature extraction method.");
    }
}

SettingFeature::Parameter SettingFeature::getParameter() const
{
    return this->_parameter;
}

void SettingFeature::setHoGParameter(int windowW, int windowH, int blockW, int blockH, int cellW, int cellH, int shiftW, int shiftH, int nBins)
{
    this->_parameter.hog = { windowW, windowH, blockW, blockH, cellW, cellH, shiftW, shiftH, nBins };
}

void SettingFeature::setPHoGParameter(int windowW, int windowH, int nBins, int layer)
{
    this->_parameter.pHog = { windowW, windowH, nBins, layer };
}

void SettingFeature::saveParameter(const char *filePath) const
{
    fstream fout;
    fout.open(filePath, ios::out);
    fout << "Edge: " << SettingControl::getInstance().detect.getUniqueString() << endl;
    switch (this->_method)
    {
    case METHOD_HOG:
        fout << "Feature: HoG" << endl;
        fout << "Window Width: " << this->_parameter.hog.windowW << endl;
        fout << "Window Height: " << this->_parameter.hog.windowH << endl;
        fout << "Block Width: " << this->_parameter.hog.blockW << endl;
        fout << "Block Height: " << this->_parameter.hog.blockH << endl;
        fout << "Cell Width: " << this->_parameter.hog.cellW << endl;
        fout << "Cell Height: " << this->_parameter.hog.cellH << endl;
        fout << "Shift Width: " << this->_parameter.hog.shiftW << endl;
        fout << "Shift Height: " << this->_parameter.hog.shiftH << endl;
        fout << "Bin Number: " << this->_parameter.hog.nBins << endl;
        break;
    case METHOD_PHOG:
        fout << "Feature: PHoG" << endl;
        fout << "Window Width: " << this->_parameter.pHog.windowW << endl;
        fout << "Window Height: " << this->_parameter.pHog.windowH << endl;
        fout << "Bin Number: " << this->_parameter.pHog.nBins << endl;
        fout << "Layer: " << this->_parameter.pHog.layer << endl;
        break;
    case METHOD_SHOG:
        break;
    case METHOD_BHOG:
        break;
    default:
        assert("Undefined feature extraction method.");
    }
    fout.flush();
    fout.close();
}

vector<double> SettingFeature::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back((double)SettingControl::getInstance().detect.getUniqueNumber());
    unique.push_back(this->_method);
    switch (this->_method)
    {
    case METHOD_HOG:
        unique.push_back(this->_parameter.hog.windowW);
        unique.push_back(this->_parameter.hog.windowH);
        unique.push_back(this->_parameter.hog.blockW);
        unique.push_back(this->_parameter.hog.blockH);
        unique.push_back(this->_parameter.hog.cellW);
        unique.push_back(this->_parameter.hog.cellH);
        unique.push_back(this->_parameter.hog.shiftW);
        unique.push_back(this->_parameter.hog.shiftH);
        unique.push_back(this->_parameter.hog.nBins);
        break;
    case METHOD_PHOG:
        unique.push_back(this->_parameter.pHog.windowW);
        unique.push_back(this->_parameter.pHog.windowH);
        unique.push_back(this->_parameter.pHog.nBins);
        unique.push_back(this->_parameter.pHog.layer);
        break;
    case METHOD_SHOG:
        break;
    case METHOD_BHOG:
        break;
    default:
        assert("Undefined feature extraction method.");
    }
    return unique;
}