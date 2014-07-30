#pragma once
#include "Detector.h"

class DetectorCanny :
    public Detector
{
public:
    DetectorCanny();
    virtual ~DetectorCanny();

    virtual void detect(const char *srcPath, const char *dstPath) override final;
};

