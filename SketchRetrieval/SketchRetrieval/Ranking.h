#pragma once

#include <vector>
#include <string>

class Ranking
{
public:
    Ranking();
    virtual ~Ranking();
    virtual void ranking(std::string sketchPath, std::vector<std::string> imagePath, std::vector<std::string> imageName, std::string resultPath) = 0;
};

