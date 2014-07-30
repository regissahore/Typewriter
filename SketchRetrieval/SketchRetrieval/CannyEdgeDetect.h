#pragma once

class CannyEdgeDetect
{
public:
    CannyEdgeDetect();
    virtual ~CannyEdgeDetect();

    void detect(const char *source, const char *target);
};

