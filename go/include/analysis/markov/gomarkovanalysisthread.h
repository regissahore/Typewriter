#ifndef GOMARKOVANALYSISTHREAD_H
#define GOMARKOVANALYSISTHREAD_H
#include <memory>
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
    std::shared_ptr<GoMarkovGraph> graph() const;
    void setGoMarkovGraph(std::shared_ptr<GoMarkovGraph> graph);
    std::shared_ptr<GoMarkovChartData> analysisResult() const;

protected:
    double _totalTime;
    int _totalCount;
    std::shared_ptr<GoMarkovGraph> _graph;
    std::shared_ptr<GoMarkovChartData> _chart;
};

#endif // GOMARKOVANALYSISTHREAD_H
