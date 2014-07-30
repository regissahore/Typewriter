#include "SettingDataset.h"
#include "SettingControl.h"
#include "Dataset.h"
using namespace std;

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}

string Dataset::getBasePath() const
{
    return this->_basePath;
}

string Dataset::getImageFolder() const
{
    return this->_imageFolder;
}

string Dataset::getSketchFolder() const
{
    return this->_sketchFolder;
}