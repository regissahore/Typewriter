#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>

#include "SettingControl.h"
#include "SettingDataset.h"
#include "SettingDetection.h"
#include "SettingFeature.h"

#include "EdgeDetection.h"
#include "FeatureExtraction.h"
#include "DistanceRanking.h"
#include "EvaluateResult.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    string line;
    EdgeDetection detection;
    FeatureExtraction extraction;
    DistanceRanking ranking;
    EvaluateResult evaluator;
    SettingControl& control = SettingControl::getInstance();
    int bestIndex = 0;
    double bestResult = 0.0;
    control.detect.setCannyParameter(128, 128, 170, 250);
    for (int layer = 3; (1 << layer) <= 128; ++layer)
    {
        control.feature.selectMethod(SettingFeature::METHOD_PHOG);
        control.feature.setPHoGParameter(128, 128, 9, layer);
        cout << "Edge Detection" << endl;
        detection.detect();
        cout << "Feature Extraction" << endl;
        extraction.extract();
        cout << "Image Ranking" << endl;
        ranking.ranking();
        cout << "Result Evaluation" << endl;
        double result = evaluator.evaluate();
        control.finishExperiment();
        if (result > bestResult)
        {
            bestResult = result;
            bestIndex = control.getExperimentIndex();
        }
        cout << "=========================== Best: " << bestResult << " " << bestIndex << endl;
    }
    getline(cin, line);
	return 0;
}

