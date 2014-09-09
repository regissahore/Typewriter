#include <fstream>
#include <algorithm>
#include "RankingEucilid.h"
using namespace std;

RankingEucilid::RankingEucilid()
{
}

RankingEucilid::~RankingEucilid()
{
}

void RankingEucilid::ranking(string sketchPath, vector<string> imagePath, std::vector<std::string> imageName, string resultPath)
{
    vector<float> sketchFeature;
    vector<float> imageFeature;
    vector<DistNode> dists;
    sketchFeature = readFeature(sketchPath);
    for (unsigned int i = 0; i < imagePath.size(); ++i)
    {
        imageFeature = readFeature(imagePath[i]);
        double dist = 0.0;
        for (unsigned int j = 0; j < sketchFeature.size(); ++j)
        {
            dist += (sketchFeature[j] - imageFeature[j]) * (sketchFeature[j] - imageFeature[j]);
        }
        dists.push_back({ dist, imageName[i] });
    }
    sort(dists.begin(), dists.end());
    fstream fout;
    fout.open(resultPath.c_str(), ios::out);
    for (auto dist : dists)
    {
        fout << dist.name << endl;
    }
    fout.flush();
    fout.close();
}

vector<float> RankingEucilid::readFeature(string path) const
{
    vector<float> feature;
    fstream fin;
    float value;
    fin.open(path.c_str(), ios::in);
    while (fin >> value)
    {
        feature.push_back(value);
    }
    fin.close();
    return feature;
}