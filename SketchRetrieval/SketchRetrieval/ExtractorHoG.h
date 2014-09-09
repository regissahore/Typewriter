#pragma once
#include "Extractor.h"

class ExtractorHoG :
    public Extractor
{
public:
    ExtractorHoG();
    virtual ~ExtractorHoG();
    virtual void extract(const char *srcPath, const char *dstPath) override final;
};

