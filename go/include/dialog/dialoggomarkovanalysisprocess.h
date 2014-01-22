#ifndef DIALOGGOMARKOVANALYSISPROCESS_H
#define DIALOGGOMARKOVANALYSISPROCESS_H

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
    void setMarkovGraph(GoMarkovGraph *graph);
    void setTotalTime(const double value);
    void setTotalCount(const int value);
    GoMarkovChartData* analysisResult() const;
    int exec();

protected:
    GoMarkovGraph *_graph;
    GoMarkovChartData *_chart;
    double _totalTime;
    int _totalCount;
    int _timeCount;
    int _operatorNum;
    QTimer *_timer;
    GoMarkovAnalysisThread *_analysisThread;

protected slots:
    void finishedEvent();
    void timeoutEvent();
    
private slots:
    void on_cancelButton_clicked();

private:
    Ui::DialogGoMarkovAnalysisProcess *ui;
};

#endif // DIALOGGOMARKOVANALYSISPROCESS_H
