#pragma once

class Detector
{
public:
    Detector();
    virtual ~Detector();
    virtual void detect(const char *srcPath, const char *dstPath) = 0;
};

