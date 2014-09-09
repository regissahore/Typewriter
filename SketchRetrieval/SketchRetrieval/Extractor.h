#pragma once

class Extractor
{
public:
    Extractor();
    ~Extractor();
    virtual void extract(const char *srcPath, const char *dstPath) = 0;
};

