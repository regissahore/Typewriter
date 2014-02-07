#ifndef DIALOGGOMARKOVANALYSISPROCESS_H
#define DIALOGGOMARKOVANALYSISPROCESS_H
#include <memory>
#include <QDialog>

class QTimer;
class GoMarkovGraph;
class GoMarkovChartData;
class GoMarkovAnalysisThread;


namespace Ui {
class DialogGoMarkovAnalysisProcess;
}

class DialogGoMarkovAnalysisProcess : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogGoMarkovAnalysisProcess(QWidget *parent = 0);
    ~DialogGoMarkovAnalysisProcess();
    void setMarkovGraph(std::shared_ptr<GoMarkovGraph> graph);
    void setTotalTime(const double value);
    void setTotalCount(const int value);
    std::shared_ptr<GoMarkovChartData> analysisResult() const;
    int exec();

protected:
    std::shared_ptr<GoMarkovGraph> _graph;
    std::shared_ptr<GoMarkovChartData> _chart;
    double _totalTime;
    int _totalCount;
    int _timeCount;
    int _operatorNum;
    std::shared_ptr<QTimer> _timer;
    std::shared_ptr<GoMarkovAnalysisThread> _analysisThread;

protected slots:
    void finishedEvent();
    void timeoutEvent();
    
private slots:
    void on_cancelButton_clicked();

private:
    Ui::DialogGoMarkovAnalysisProcess *ui;
};

#endif // DIALOGGOMARKOVANALYSISPROCESS_H
