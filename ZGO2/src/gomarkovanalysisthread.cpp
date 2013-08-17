#include "gomarkovanalysisthread.h"
#include "gomarkovgraph.h"

GOMarkovAnalysisThread::GOMarkovAnalysisThread()
{
    this->_graph = 0L;
    this->_chart = 0L;
}

void GOMarkovAnalysisThread::run()
{
    if (this->graph() != 0L)
    {
        this->_chart = this->graph()->calcAccumulativeProbability(this->totalTime(), this->totalCount());
    }
}

double GOMarkovAnalysisThread::totalTime() const
{
    return this->_totalTime;
}

void GOMarkovAnalysisThread::setTotalTime(const double value)
{
    this->_totalTime = value;
}

double GOMarkovAnalysisThread::currentTime() const
{
    if (this->graph() != 0L)
    {
        return this->_totalTime / this->_totalCount * this->graph()->currentCount();
    }
    return 0.0;
}

int GOMarkovAnalysisThread::totalCount() const
{
    return this->_totalCount;
}

void GOMarkovAnalysisThread::setTotalCount(const int value)
{
    this->_totalCount = value;
}

int GOMarkovAnalysisThread::currentCount() const
{
    if (this->graph() != 0L)
    {
        return this->graph()->currentCount();
    }
    return 0.0;
}

GOMarkovGraph* GOMarkovAnalysisThread::graph() const
{
    return this->_graph;
}

void GOMarkovAnalysisThread::setGOMarkovGraph(GOMarkovGraph *graph)
{
    this->_graph = graph;
}

GOMarkovChartData* GOMarkovAnalysisThread::analysisResult() const
{
    return this->_chart;
}
