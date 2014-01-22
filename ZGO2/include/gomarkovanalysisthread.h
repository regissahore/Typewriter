#ifndef GOMARKOVANALYSISTHREAD_H
#define GOMARKOVANALYSISTHREAD_H
#include <QThread>

class GOMarkovGraph;
class GOMarkovChartData;

class GOMarkovAnalysisThread : public QThread
{
    Q_OBJECT

public:
    GOMarkovAnalysisThread();
    void run();

    double totalTime() const;
    void setTotalTime(const double value);
    double currentTime() const;
    void setCurrentTime(const double value);
    int totalCount() const;
    void setTotalCount(const int value);
    int currentCount() const;
    int operatorNum() const;
    int operatorProcess() const;
    QString currentOperatorName() const;
    GOMarkovGraph* graph() const;
    void setGOMarkovGraph(GOMarkovGraph *graph);
    GOMarkovChartData* analysisResult() const;

protected:
    double _totalTime;
    int _totalCount;
    GOMarkovGraph *_graph;
    GOMarkovChartData *_chart;
};

#endif // GOMARKOVANALYSISTHREAD_H
