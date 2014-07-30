#pragma once
#include "Ranking.h"

class RankingEucilid :
    public Ranking
{
public:
    RankingEucilid();
    virtual ~RankingEucilid();
    virtual void ranking(std::string sketchPath, std::vector<std::string> imagePath, std::vector<std::string> imageName, std::string resultPath) override final;
};

