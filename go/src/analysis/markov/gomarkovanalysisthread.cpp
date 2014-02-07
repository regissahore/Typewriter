#include "GoMarkovAnalysisThread.h"
#include "GoMarkovGraph.h"
using namespace std;

GoMarkovAnalysisThread::GoMarkovAnalysisThread()
{
    this->_graph = nullptr;
    this->_chart = nullptr;
}

void GoMarkovAnalysisThread::run()
{
    if (this->graph() != nullptr)
    {
        this->_chart = this->graph()->calcAccumulativeProbability(this->totalTime(), this->totalCount());
    }
}

double GoMarkovAnalysisThread::totalTime() const
{
    return this->_totalTime;
}

void GoMarkovAnalysisThread::setTotalTime(const double value)
{
    this->_totalTime = value;
}

double GoMarkovAnalysisThread::currentTime() const
{
    if (this->graph() != nullptr)
    {
        return this->_totalTime / this->_totalCount * this->graph()->timeProcess();
    }
    return 0.0;
}

int GoMarkovAnalysisThread::totalCount() const
{
    return this->_totalCount;
}

void GoMarkovAnalysisThread::setTotalCount(const int value)
{
    this->_totalCount = value;
}

int GoMarkovAnalysisThread::currentCount() const
{
    if (this->graph() != nullptr)
    {
        return this->graph()->timeProcess();
    }
    return 0;
}

int GoMarkovAnalysisThread::operatorNum() const
{
    if (this->graph() != nullptr)
    {
        return this->graph()->totalOperatorNum();
    }
    return 0;
}

int GoMarkovAnalysisThread::operatorProcess() const
{
    if (this->graph() != nullptr)
    {
        return this->graph()->operatorProcess();
    }
    return 0;
}

QString GoMarkovAnalysisThread::currentOperatorName() const
{
    if (this->graph() != nullptr)
    {
        return this->graph()->currentOperatorName();
    }
    return "";
}

shared_ptr<GoMarkovGraph> GoMarkovAnalysisThread::graph() const
{
    return this->_graph;
}

void GoMarkovAnalysisThread::setGoMarkovGraph(shared_ptr<GoMarkovGraph> graph)
{
    this->_graph = graph;
}

shared_ptr<GoMarkovChartData> GoMarkovAnalysisThread::analysisResult() const
{
    return this->_chart;
}
