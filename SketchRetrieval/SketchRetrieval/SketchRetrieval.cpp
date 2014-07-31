// SketchRetrieval.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EdgeDetection.h"
#include "FeatureExtraction.h"
#include "DistanceRanking.h"

int _tmain(int argc, _TCHAR* argv[])
{
    EdgeDetection detection;
    detection.detect();
    FeatureExtraction extraction;
    extraction.extract();
    DistanceRanking ranking;
    ranking.ranking();
	return 0;
}

