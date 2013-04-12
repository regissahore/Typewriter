#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
/**
 *
 */
#include "gograph.h"

class GOMarkovGraph : public GOGraph
{
public:
    GOMarkovGraph();
    bool saveAsHTML(const QString filePath);
};

#endif // GOMARKOVGRAPH_H
