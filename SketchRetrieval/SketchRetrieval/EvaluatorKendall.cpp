#include <map>
#include <fstream>
#include "EvaluatorKendall.h"
using namespace std;

EvaluatorKendall::EvaluatorKendall()
{
}

EvaluatorKendall::~EvaluatorKendall()
{
}

double EvaluatorKendall::evaluate(vector<string> categories, string truthFolder, string expFolder, string resultFolder)
{
    vector<double> kendalls;
    fstream fin, fout;
    int order;
    string name;
    fout.open((resultFolder + "results.txt"), ios::out);
    for (auto cat : categories)
    {
        string truthPath = truthFolder + cat;
        string expPath = expFolder + cat;
        vector<string> images;
        map<string, int> truthOrder;
        fin.open(truthPath.c_str(), ios::in);
        order = 0;
        while (fin >> name)
        {
            truthOrder[name] = order++;
            images.push_back(name);
        }
        fin.close();
        map<string, int> expOrder;
        fin.open(expPath.c_str(), ios::in);
        order = 0;
        while (fin >> name)
        {
            expOrder[name] = order++;
        }
        fin.close();
        int n = images.size();
        int nc = 0;
        int nd = 0;
        for (unsigned int i = 0; i < images.size(); ++i)
        {
            for (unsigned int j = i + 1; j < images.size(); ++j)
            {
                if ((truthOrder[images[i]] - truthOrder[images[j]]) * (expOrder[images[i]] - expOrder[images[j]]) > 0)
                {
                    ++nc;
                }
                else
                {
                    ++nd;
                }
            }
        }
        double kendall = 1.0 * (nc - nd) / ((n * (n - 1)) >> 1);
        fout << cat << " " << kendall << endl;
        kendalls.push_back(kendall);
    }
    fout.flush();
    fout.close();
    double meanKendall = 0.0;
    for (auto k : kendalls)
    {
        meanKendall += k;
    }
    meanKendall /= kendalls.size();
    fout.open((resultFolder + "result.txt"), ios::out);
    fout << meanKendall << endl;
    fout.flush();
    fout.close();
    return meanKendall;
}