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
        return this->_totalTime / this->_totalCount * this->graph()->timeProcess();
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
        return this->graph()->timeProcess();
    }
    return 0;
}

int GOMarkovAnalysisThread::operatorNum() const
{
    if (this->graph() != 0L)
    {
        return this->graph()->totalOperatorNum();
    }
    return 0;
}

int GOMarkovAnalysisThread::operatorProcess() const
{
    if (this->graph() != 0L)
    {
        return this->graph()->operatorProcess();
    }
    return 0;
}

QString GOMarkovAnalysisThread::currentOperatorName() const
{
    if (this->graph() != 0L)
    {
        return this->graph()->currentOperatorName();
    }
    return "";
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
