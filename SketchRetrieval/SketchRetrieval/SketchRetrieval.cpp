// SketchRetrieval.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EdgeDetection.h"
#include "FeatureExtraction.h"

int _tmain(int argc, _TCHAR* argv[])
{
    EdgeDetection edgeDetection;
    edgeDetection.detect();
    FeatureExtraction extraction;
    extraction.extract();
	return 0;
}

