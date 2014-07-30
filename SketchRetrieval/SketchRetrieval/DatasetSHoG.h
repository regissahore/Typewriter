#pragma once
#include <map>
#include "Dataset.h"

class DatasetSHoG :
    public Dataset
{
public:
    DatasetSHoG();
    virtual ~DatasetSHoG();

    virtual std::vector<std::string> getCategoryList() override final;
    virtual std::vector<std::string> getSketchList() override final;
    virtual std::string getSketch(std::string category) override final;
    virtual std::vector<std::string> getImageList() override final;
    virtual std::vector<std::string> getImageList(std::string category) override final;
    virtual std::vector<std::string> getImageNames() override final;
    virtual std::vector<std::string> getImageNames(std::string category) override final;

private:
    bool _initialized;
    std::vector<std::string> _categories;
    std::vector<std::string> _sketchList;
    std::vector<std::string> _imageList;
    std::vector<std::string> _nameList;
    std::map<std::string, std::string> _sketchMap;
    std::map<std::string, std::vector<std::string>> _imageMap;
    std::map<std::string, std::vector<std::string>> _nameMap;

    void initInfo();
};

