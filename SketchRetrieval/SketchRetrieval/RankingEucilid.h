#pragma once
#include "Ranking.h"

class RankingEucilid :
    public Ranking
{
public:
    RankingEucilid();
    virtual ~RankingEucilid();
    virtual void ranking(std::string sketchPath, std::vector<std::string> imagePath, std::vector<std::string> imageName, std::string resultPath) override final;

private:
    struct DistNode
    {
        double dist;
        std::string name;
        bool operator <(const DistNode &node) const
        {
            return dist < node.dist;
        }
    };

    std::vector<float> readFeature(std::string path) const;
};

