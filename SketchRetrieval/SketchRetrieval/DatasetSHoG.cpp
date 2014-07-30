#include <fstream>
#include "DatasetSHoG.h"
using namespace std;

DatasetSHoG::DatasetSHoG()
{
    this->_initialized = false;
    this->_basePath = "Dataset/SHoG/";
    this->_imageFolder = "images/";
    this->_sketchFolder = "sketches/";
}

DatasetSHoG::~DatasetSHoG()
{
}

vector<string> DatasetSHoG::getCategoryList()
{
    if (!this->_initialized)
    {
        this->initInfo();
    }
    return this->_categories;
}

vector<string> DatasetSHoG::getSketchList()
{
    if (!this->_initialized)
    {
        this->initInfo();
    }
    return this->_sketchList;
}

vector<string> DatasetSHoG::getSketchList(string category)
{
    if (!this->_initialized)
    {
        this->initInfo();
    }
    return this->_sketchMap[category];
}

vector<string> DatasetSHoG::getImageList()
{
    if (!this->_initialized)
    {
        this->initInfo();
    }
    return this->_imageList;
}

vector<string> DatasetSHoG::getImageList(string category)
{
    if (!this->_initialized)
    {
        this->initInfo();
    }
    return this->_imageMap[category];
}

void DatasetSHoG::initInfo()
{
    fstream file;
    string sketchFile = this->_basePath + "/sketches.order";
    file.open(sketchFile.c_str(), ios::in);
    while (!file.eof())
    {
        string sketch;
        file >> sketch;
        string cat = sketch.substr(0, sketch.length() - 4);
        this->_categories.push_back(cat);
        this->_sketchList.push_back(sketch);
        this->_sketchMap[cat].push_back(sketch);
    }
    file.close();
    string imageFile = this->_basePath + "/images.order";
    file.open(imageFile.c_str(), ios::in);
    for (auto cat : this->_categories)
    {
        for (int i = 0; i < 40; ++i)
        {
            string image;
            file >> image;
            this->_imageList.push_back(image);
            this->_imageMap[cat].push_back(image);
        }
    }
    file.close();
    this->_initialized = true;
}