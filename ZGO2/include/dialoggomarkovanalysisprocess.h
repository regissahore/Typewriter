#ifndef DIALOGGOMARKOVANALYSISPROCESS_H
#define DIALOGGOMARKOVANALYSISPROCESS_H

#include <QDialog>

class QTimer;
class GOMarkovGraph;
class GOMarkovChartData;
class GOMarkovAnalysisThread;


namespace Ui {
class DialogGOMarkovAnalysisProcess;
}

class DialogGOMarkovAnalysisProcess : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogGOMarkovAnalysisProcess(QWidget *parent = 0);
    ~DialogGOMarkovAnalysisProcess();
    void setMarkovGraph(GOMarkovGraph *graph);
    void setTotalTime(const double value);
    void setTotalCount(const int value);
    GOMarkovChartData* analysisResult() const;
    int exec();

protected:
    GOMarkovGraph *_graph;
    GOMarkovChartData *_chart;
    double _totalTime;
    int _totalCount;
    int _timeCount;
    QTimer *_timer;
    GOMarkovAnalysisThread *_analysisThread;

protected slots:
    void finishedEvent();
    void timeoutEvent();
    
private slots:
    void on_cancelButton_clicked();

private:
    Ui::DialogGOMarkovAnalysisProcess *ui;
};

#endif // DIALOGGOMARKOVANALYSISPROCESS_H
