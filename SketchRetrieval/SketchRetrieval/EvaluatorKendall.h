#pragma once
#include "Evaluator.h"

class EvaluatorKendall :
    public Evaluator
{
public:
    EvaluatorKendall();
    virtual ~EvaluatorKendall();

    double evaluate(std::vector<std::string> categories, std::string truthFolder, std::string expFolder, std::string resultFolder);
};

