#pragma once
#include <vector>
#include <string>

class Dataset
{
public:
    Dataset();
    virtual ~Dataset();

    std::string getBasePath() const;
    std::string getImageFolder() const;
    std::string getSketchFolder() const;
    std::string getTruthFolder() const;
    virtual std::vector<std::string> getCategoryList() = 0;
    virtual std::vector<std::string> getSketchList() = 0;
    virtual std::string getSketch(std::string category) = 0;
    virtual std::vector<std::string> getImageList() = 0;
    virtual std::vector<std::string> getImageList(std::string category) = 0;
    virtual std::vector<std::string> getImageNames() = 0;
    virtual std::vector<std::string> getImageNames(std::string category) = 0;

protected:
    std::string _basePath;
    std::string _imageFolder;
    std::string _sketchFolder;
    std::string _truthFolder;
};

