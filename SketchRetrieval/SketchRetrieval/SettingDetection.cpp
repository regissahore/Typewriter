#include <fstream>
#include <cassert>
#include "SettingDetection.h"
#include "SettingDataset.h"
#include "SettingControl.h"
using namespace std;

SettingDetection::SettingDetection()
{
    this->_settingName = "Detection";
    this->selectMethod(METHOD_CANNY);
}

SettingDetection::~SettingDetection()
{
}

SettingDetection::Method SettingDetection::getMethod() const
{
    return this->_method;
}

void SettingDetection::selectMethod(Method method)
{
    this->_method = method;
    switch (method)
    {
    case METHOD_CANNY:
        this->setCannyParameter();
        break;
    default:
        assert("Edge detection method is not defined.");
    }
}

void SettingDetection::setCannyParameter(int windowW, int windowH, double thresholdLow, double thresholdHigh, int apertureSize)
{
    this->_parameters.canny = { windowW, windowH, thresholdLow, thresholdHigh, apertureSize };
}

SettingDetection::Paramters SettingDetection::getParameters() const
{
    return this->_parameters;
}

vector<double> SettingDetection::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back((double)SettingControl::getInstance().dataset.getUniqueNumber());
    unique.push_back(this->_method);
    switch (this->_method)
    {
    case METHOD_CANNY:
        unique.push_back(this->_parameters.canny.windowW);
        unique.push_back(this->_parameters.canny.windowH);
        unique.push_back(this->_parameters.canny.thresholdLow);
        unique.push_back(this->_parameters.canny.thresholdHigh);
        unique.push_back((double)this->_parameters.canny.apertureSize);
        break;
    default:
        assert("Edge detection method is not defined.");
    }
    return unique;
}

void SettingDetection::saveParameter(const char *filePath) const
{
    fstream fout;
    fout.open(filePath, ios::out);
    fout << "Dataset: ";
    switch (SettingControl::getInstance().dataset.getDatasetEnum())
    {
    case SettingDataset::DATASET_SHOG:
        fout << "SHoG";
        break;
    default:
        assert("No such dataset.");
    }
    fout << endl;
    switch (this->_method)
    {
    case METHOD_CANNY:
        fout << "Method: Canny" << endl;
        fout << "Width: " << this->_parameters.canny.windowW << endl;
        fout << "Height: " << this->_parameters.canny.windowH << endl;
        fout << "Threshold Low: " << this->_parameters.canny.thresholdLow << endl;
        fout << "Threshold High: " << this->_parameters.canny.thresholdHigh << endl;
        fout << "Aperture Size: " << this->_parameters.canny.apertureSize << endl;
        break;
    default:
        assert("Edge detection method is not defined.");
    }
    fout.flush();
    fout.close();
}