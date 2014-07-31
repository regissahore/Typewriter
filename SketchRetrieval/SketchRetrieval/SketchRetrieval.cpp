#include "stdafx.h"
#include <string>
#include <iostream>
#include "EdgeDetection.h"
#include "FeatureExtraction.h"
#include "DistanceRanking.h"
#include "EvaluateResult.h"
#include "SettingControl.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    string line;
    EdgeDetection detection;
    detection.detect();
    FeatureExtraction extraction;
    extraction.extract();
    DistanceRanking ranking;
    ranking.ranking();
    EvaluateResult evaluator;
    evaluator.evaluate();
    SettingControl::getInstance().finishExperiment();
    getline(cin, line);
	return 0;
}

