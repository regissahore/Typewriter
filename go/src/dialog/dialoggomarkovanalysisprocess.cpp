#include <QTimer>
#include "DialogGoMarkovAnalysisProcess.h"
#include "ui_dialoggomarkovanalysisprocess.h"
#include "GoMarkovGraph.h"
#include "GoMarkovChartData.h"
#include "GoMarkovAnalysisThread.h"

DialogGoMarkovAnalysisProcess::DialogGoMarkovAnalysisProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGoMarkovAnalysisProcess)
{
    ui->setupUi(this);
    this->_timeCount = 0;
    this->_graph = 0;
    this->_analysisThread = new GoMarkovAnalysisThread();
}

DialogGoMarkovAnalysisProcess::~DialogGoMarkovAnalysisProcess()
{
    delete ui;
    delete this->_analysisThread;
    this->_timer->stop();
    delete this->_timer;
}

void DialogGoMarkovAnalysisProcess::setMarkovGraph(GoMarkovGraph *graph)
{
    this->_graph = graph;
    this->_operatorNum = graph->totalOperatorNum();
}

GoMarkovChartData* DialogGoMarkovAnalysisProcess::analysisResult() const
{
    return this->_chart;
}

int DialogGoMarkovAnalysisProcess::exec()
{
    this->_analysisThread->setGoMarkovGraph(this->_graph);
    this->_analysisThread->setTotalTime(this->_totalTime);
    this->_analysisThread->setTotalCount(this->_totalCount);
    this->connect(this->_analysisThread, SIGNAL(finished()), this, SLOT(finishedEvent()));
    this->_analysisThread->start();

    this->_timer = new QTimer();
    this->_timer->setInterval(20);
    this->connect(this->_timer, SIGNAL(timeout()), this, SLOT(timeoutEvent()));
    this->_timer->start();

    return this->QDialog::exec();
}

void DialogGoMarkovAnalysisProcess::setTotalTime(const double value)
{
    this->_totalTime = value;
}

void DialogGoMarkovAnalysisProcess::setTotalCount(const int value)
{
    this->_totalCount = value;
}

void DialogGoMarkovAnalysisProcess::finishedEvent()
{
    this->_chart = this->_analysisThread->analysisResult();
    this->accept();
}

void DialogGoMarkovAnalysisProcess::timeoutEvent()
{
    ++this->_timeCount;
    int time = this->_timeCount / 50;
    this->ui->lineEditTimePassed->setText("");
    if (time >= 3600)
    {
        this->ui->lineEditTimePassed->setText(this->ui->lineEditTimePassed->text() + QObject::tr("%1 Hour ").arg(time / 3600));
    }
    if (time >= 60)
    {
        this->ui->lineEditTimePassed->setText(this->ui->lineEditTimePassed->text() + QObject::tr("%1 Minute ").arg((time % 3600) / 60));
    }
    this->ui->lineEditTimePassed->setText(this->ui->lineEditTimePassed->text() + QObject::tr("%1 Second").arg(time % 60));

    QString totalTime = QString::number(this->_analysisThread->totalTime(), 'f', 2);
    QString currentTime = QString::number(this->_analysisThread->currentTime(), 'f', 2);
    this->ui->lineEditTimeProcess->setText(currentTime + " / " + totalTime);

    this->ui->lineEditOperatorProcess->setText(QString("%1 / %2").arg(this->_analysisThread->operatorProcess() + 1).arg(this->_operatorNum));
    this->ui->lineEditCurrentOperator->setText(this->_analysisThread->currentOperatorName());

    int currentCount = this->_analysisThread->currentCount();
    this->ui->lineEditCountProcess->setText(QString("%1 / %2").arg(currentCount).arg(this->_totalCount));

    this->ui->progressBarOperator->setMaximum(this->_operatorNum);
    this->ui->progressBarOperator->setValue(this->_analysisThread->operatorProcess() + 1);
    this->ui->progressBar->setMaximum(this->_totalCount * this->_operatorNum);
    this->ui->progressBar->setValue(this->_analysisThread->currentCount() * this->_operatorNum + this->_analysisThread->operatorProcess() + 1);
}

void DialogGoMarkovAnalysisProcess::on_cancelButton_clicked()
{
    this->_analysisThread->quit();
    while(!this->_analysisThread->isFinished());
    this->reject();
}
