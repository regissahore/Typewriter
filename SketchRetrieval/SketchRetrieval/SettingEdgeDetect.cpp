#include <fstream>
#include <cassert>
#include "SettingEdgeDetect.h"
#include "SettingDataset.h"
#include "SettingControl.h"
using namespace std;

SettingEdgeDetect::SettingEdgeDetect()
{
    this->_settingName = "EdgeDetection";
    this->selectMethod(METHOD_CANNY);
}

SettingEdgeDetect::~SettingEdgeDetect()
{
}

SettingEdgeDetect::Method SettingEdgeDetect::getMethod() const
{
    return this->_method;
}

void SettingEdgeDetect::selectMethod(Method method)
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

void SettingEdgeDetect::setCannyParameter(int windowW, int windowH, double thresholdLow, double thresholdHigh, int apertureSize)
{
    this->_parameters.canny = { windowW, windowH, thresholdLow, thresholdHigh, apertureSize };
}

SettingEdgeDetect::Paramters SettingEdgeDetect::getParameters() const
{
    return this->_parameters;
}

vector<double> SettingEdgeDetect::getUniqueVector() const
{
    vector<double> unique;
    unique.push_back((double)SettingControl::getInstance().dataset.getUniqueNumber());
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

void SettingEdgeDetect::saveParameter(const char *filePath) const
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