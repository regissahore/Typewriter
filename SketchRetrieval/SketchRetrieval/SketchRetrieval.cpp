// SketchRetrieval.cpp : �������̨Ӧ�ó������ڵ㡣
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

