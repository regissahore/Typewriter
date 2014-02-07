#ifndef GOMARKOVANALYSISTHREAD_H
#define GOMARKOVANALYSISTHREAD_H
#include <QSharedPointer>
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
    QSharedPointer<GoMarkovGraph> graph() const;
    void setGoMarkovGraph(QSharedPointer<GoMarkovGraph> graph);
    QSharedPointer<GoMarkovChartData> analysisResult() const;

protected:
    double _totalTime;
    int _totalCount;
    QSharedPointer<GoMarkovGraph> _graph;
    QSharedPointer<GoMarkovChartData> _chart;
};

#endif // GOMARKOVANALYSISTHREAD_H
