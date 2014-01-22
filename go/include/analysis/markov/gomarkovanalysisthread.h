#ifndef GOMARKOVANALYSISTHREAD_H
#define GOMARKOVANALYSISTHREAD_H
#include <QThread>

class GoMarkovGraph;
class GoMarkovChartData;

class GoMarkovAnalysisThread : public QThread
{
    Q_OBJECT

public:
    GoMarkovAnalysisThread();
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
    GoMarkovGraph* graph() const;
    void setGoMarkovGraph(GoMarkovGraph *graph);
    GoMarkovChartData* analysisResult() const;

protected:
    double _totalTime;
    int _totalCount;
    GoMarkovGraph *_graph;
    GoMarkovChartData *_chart;
};

#endif // GOMARKOVANALYSISTHREAD_H
