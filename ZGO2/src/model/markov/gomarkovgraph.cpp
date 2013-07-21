#include <cstdio>
#include <QString>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <qmath.h>
#include "gostatus.h"
#include "goaccumulative.h"
#include "gomarkovgraph.h"
#include "gomarkovanalysis.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "gomarkovchartdata.h"
#include "gomarkovoperatorfactory.h"
#include "goinput.h"
#include "gooutput.h"
#include "gosignal.h"
#include "gomarkovcommoncause.h"

GOMarkovGraph::GOMarkovGraph() : GOGraph()
{
    delete this->_analysis;
    this->_analysis = new GOMarkovAnalysis();
}

GOMarkovGraph::~GOMarkovGraph()
{
    this->GOGraph::~GOGraph();
    this->_equivalent.clear();
}

QVector<GOMarkovEquivalent*> GOMarkovGraph::getEquivalent() const
{
    return this->_equivalent;
}

void GOMarkovGraph::addEquivalent(GOMarkovEquivalent *equivalent)
{
    this->_equivalent.push_back(equivalent);
}

QVector<GOMarkovCommonCause*> GOMarkovGraph::getCommonCause() const
{
    return this->_commonCause;
}

void GOMarkovGraph::addCommonCause(GOMarkovCommonCause *commonCause)
{
    this->_commonCause.push_back(commonCause);
}

void GOMarkovGraph::calcAccumulativeProbability(double time)
{
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        return;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        QVector<GOGraph::Output> commonList;
        if (list[i]->input()->number() + list[i]->subInput()->number() > 1)
        {
            commonList = this->getCommonSignalList(list[i]);
        }
        if (commonList.size() == 0)
        {
            ((GOMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GOMarkovOperator*)list[i], time);
        }
        else
        {
            QVector<GOOperator*> commonOperator;
            QVector<int> commonIndex;
            for (int j = 0; j < commonList.size(); ++j)
            {
                commonOperator.push_back(commonList[j].op);
                commonIndex.push_back(commonList[j].outputIndex);
            }
            ((GOMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GOMarkovOperator*)list[i], commonOperator, commonIndex, time);
        }
    }
    list.clear();
}

/**
 * Calculate the accumulative probability with the probability changed with the time.
 * @param totalTime The total time of the calculation.
 * @param count The time the calculation does.
 */
GOMarkovChartData *GOMarkovGraph::calcAccumulativeProbability(double totalTime, int count)
{
    GOMarkovChartData *data = new GOMarkovChartData();
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        if (this->_operator[i]->output()->number() == 1)
        {
            data->names.push_back(QString("%1").arg(this->_operator[i]->id()));
            data->probabilities.push_back(QVector<double>());
            data->lambdas.push_back(QVector<double>());
            data->mius.push_back(QVector<double>());
        }
        else
        {
            for (int j = 0; j < this->_operator[i]->output()->number(); ++j)
            {
                data->names.push_back(QString("%1 (%2)").arg(this->_operator[i]->id()).arg(j + 1));
                data->probabilities.push_back(QVector<double>());
                data->lambdas.push_back(QVector<double>());
                data->mius.push_back(QVector<double>());
            }
        }
    }
    for (int i = 0; i < count; ++i)
    {
        // Record initial value of lamda.
        QVector<double> lamdas;
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            lamdas.push_back(op->markovStatus()->frequencyBreakdown());
        }
        // Calculate without common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(op->markovStatus()->frequencyBreakdown() + this->_commonCause[j]->commonCause());
            }
        }
        double time = i * totalTime / (count - 1);
        data->times.push_back(time);
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            double c12 = 0.0;
            for (int k = 0; k < this->_commonCause.size(); ++k)
            {
                if (this->_commonCause[k]->containOperator(op))
                {
                    c12 = this->_commonCause[k]->calcCommonCause(time);
                    break;
                }
            }
            op->initMarkovStatus(time, c12);
        }
        this->calcAccumulativeProbability(time);
        if (this->getErrorMessage() != "")
        {
            delete data;
            return 0L;
        }
        for (int j = 0, index = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[j];
            for (int k = 0; k < this->_operator[j]->output()->number(); ++k)
            {
                data->probabilities[index].push_back(op->markovOutputStatus()->at(k)->probabilityNormal());
                data->lambdas[index].push_back(op->markovOutputStatus()->at(k)->frequencyBreakdown());
                data->mius[index++].push_back(op->markovOutputStatus()->at(k)->frequencyRepair());
            }
        }
        // Fixed the error caused by common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            QVector<double> r00;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(1e100);
            }
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[k];
                op->initMarkovStatus(time);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[k];
                for (int l = 0; l < this->_operator[k]->output()->number(); ++l)
                {
                    r00.push_back(op->accmulatives()->at(l)->probability(1));
                }
            }

            QVector<double> r11;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(0.0);
            }
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[k];
                op->initMarkovStatus(time);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[k];
                for (int l = 0; l < this->_operator[k]->output()->number(); ++l)
                {
                    r11.push_back(op->accmulatives()->at(l)->probability(1));
                }
            }

            double c12 = this->_commonCause[j]->calcCommonCause(time);
            for (int k = 0; k < r00.size(); ++k)
            {
                data->probabilities[k][i] += c12 * (r00[k] - r11[k]);
                if (data->probabilities[k][i] > 1.0)
                {
                    data->probabilities[k][i] = 1.0;
                }
            }
        }
        // Restore the lamda value.
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            op->markovStatus()->setFrequencyBreakdown(lamdas[j]);
        }
    }
    return data;
}

bool GOMarkovGraph::saveAsHTML(const QString filePath)
{
    this->_error = "";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        this->_error = QObject::tr("Can't open file ") + filePath;
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" + file.fileName() + "</title>" << endl;
    out << "<meta charset = UTF-8>" << endl;
    out << "<style>body{width:100%}table,td{margin:0 auto;border:1px solid #CCC;border-collapse:collapse;font:small/1.5 'Tahoma','Bitstream Vera Sans',Verdana,Helvetica,sans-serif;}table{border:none;border:1px solid #CCC;}thead th,tbody th{color:#666;padding:5px 10px;border-left:1px solid #CCC;}tbody th{background:#fafafb;border-top:1px solid #CCC;text-align:left;}tbody tr td{padding:5px 10px;color:#666;}tbody tr:hover td{color:#454545;}tfoot td,tfoot th{border-left:none;border-top:1px solid #CCC;padding:4px;color:#666;}caption{text-align:left;font-size:120%;padding:10px 0;color:#666;}table a:link{color:#666;}table a:visited{color:#666;}table a:hover{color:#003366;text-decoration:none;}table a:active{color:#003366;}</style>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<input type = hidden value = ZHG/>";
    QVector<GOOperator*> list;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        list.push_back(this->_operator[i]);
    }
    for (int i = 0; i < list.size(); ++i)
    {
        for (int j = i + 1; j < list.size(); ++j)
        {
            if (list[i]->id() > list[j]->id())
            {
                GOOperator *temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    out << "<h1>" + QObject::tr("Analysis Result") + "</h1>" << endl;
    for (int i = 0; i < list.size(); ++i)
    {
        out << "<table>" << endl;
        out << "<tr style='text-align: center;'>" << endl;
        out << "<th>";
        out << QString("%1-%2").arg(list[i]->type()).arg(list[i]->id()) << endl;
        out << "</th>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>";
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Operator") + "</th>" << endl;
        out << "<th>" + QObject::tr("Output") + "</th>" << endl;
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j < list[i]->status()->number(); ++j)
        {
            out << "<tr>" << endl;
            out << QString("<td style='text-align:center;'>%1</td>").arg(j);
            out << "<td>" << list[i]->status()->probability(j) << "</td>";
            out << "</tr>" << endl;
        }
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyBreakdown() << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyRepair() << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << QString("<td>Normal</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityNormal()) << endl;
        out << QString("<td>Breakdown</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityBreakdown()) << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown() << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown()) << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair() << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair()) << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "<br/>" << endl;
    }
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}
