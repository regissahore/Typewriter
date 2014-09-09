#include <cassert>
#include <memory>
#include <io.h>
#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingRanking.h"
#include "SettingEvaluate.h"
#include "Dataset.h"
#include "Evaluator.h"
#include "EvaluatorKendall.h"
#include "EvaluateResult.h"
using namespace std;

EvaluateResult::EvaluateResult()
{
}

EvaluateResult::~EvaluateResult()
{
}

double EvaluateResult::evaluate()
{
    SettingDataset& datasetSetting = SettingControl::getInstance().dataset;
    SettingRanking& rankingSetting = SettingControl::getInstance().ranking;
    SettingEvaluate& evaluateSetting = SettingControl::getInstance().evaluate;
    shared_ptr<Dataset> dataset = datasetSetting.getDataset();
    vector<string> categories = dataset->getCategoryList();
    string truthFolder = dataset->getBasePath() + dataset->getTruthFolder();
    string rankingFolder = rankingSetting.getFolderName();
    string resultFolder = evaluateSetting.getFolderName();
    shared_ptr<Evaluator> evaluator;
    switch (evaluateSetting.getMethod())
    {
    case SettingEvaluate::METHOD_KENDALL:
        evaluator = shared_ptr<Evaluator>(new EvaluatorKendall());
        break;
    default:
        assert("Evaluation method is not defined.");
    }
    return evaluator->evaluate(categories, truthFolder, rankingFolder, resultFolder);
}