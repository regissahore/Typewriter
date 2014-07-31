#pragma once
#include <vector>
#include <string>

class Evaluator
{
public:
    Evaluator();
    virtual ~Evaluator();
    virtual double evaluate(std::vector<std::string> categories, std::string truthFolder, std::string expFolder, std::string resultFolder) = 0;
};

