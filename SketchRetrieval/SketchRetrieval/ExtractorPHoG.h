#pragma once
#include "Extractor.h"

class ExtractorPHoG :
    public Extractor
{
public:
    ExtractorPHoG();
    virtual ~ExtractorPHoG();
    virtual void extract(const char *srcPath, const char *dstPath) override final;
};

