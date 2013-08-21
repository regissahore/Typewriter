#include <QTimer>
#include "dialoggomarkovanalysisprocess.h"
#include "ui_dialoggomarkovanalysisprocess.h"
#include "gomarkovgraph.h"
#include "gomarkovchartdata.h"
#include "gomarkovanalysisthread.h"

DialogGOMarkovAnalysisProcess::DialogGOMarkovAnalysisProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGOMarkovAnalysisProcess)
{
    ui->setupUi(this);
    this->_timeCount = 0;
    this->_graph = 0;
    this->_analysisThread = new GOMarkovAnalysisThread();
}

DialogGOMarkovAnalysisProcess::~DialogGOMarkovAnalysisProcess()
{
    delete ui;
    delete this->_analysisThread;
    this->_timer->stop();
    delete this->_timer;
}

void DialogGOMarkovAnalysisProcess::setMarkovGraph(GOMarkovGraph *graph)
{
    this->_graph = graph;
}

GOMarkovChartData* DialogGOMarkovAnalysisProcess::analysisResult() const
{
    return this->_chart;
}

int DialogGOMarkovAnalysisProcess::exec()
{
    this->_analysisThread->setGOMarkovGraph(this->_graph);
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

void DialogGOMarkovAnalysisProcess::setTotalTime(const double value)
{
    this->_totalTime = value;
}

void DialogGOMarkovAnalysisProcess::setTotalCount(const int value)
{
    this->_totalCount = value;
    this->ui->progressBar->setMaximum(value);
}

void DialogGOMarkovAnalysisProcess::finishedEvent()
{
    this->_chart = this->_analysisThread->analysisResult();
    this->accept();
}

void DialogGOMarkovAnalysisProcess::timeoutEvent()
{
    ++this->_timeCount;
    int time = this->_timeCount / 10;
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

    int currentCount = this->_analysisThread->currentCount();
    this->ui->lineEditCountProcess->setText(QString("%1 / %2").arg(currentCount).arg(this->_totalCount));

    this->ui->progressBar->setValue(currentCount);
}

void DialogGOMarkovAnalysisProcess::on_cancelButton_clicked()
{
    this->_analysisThread->terminate();
    this->reject();
}
