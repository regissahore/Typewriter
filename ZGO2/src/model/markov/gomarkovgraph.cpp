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
        data->ids.push_back(this->_operator[i]->id());
        data->types.push_back(this->_operator[i]->type());
        data->probabilities.push_back(QVector<double>());
    }
    for (int i = 0; i < count; ++i)
    {
        // Record initial value of lamda.
        QVector<BigDecimal> lamdas;
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
                op->markovStatus()->setFrequencyBreakdown(op->markovStatus()->frequencyBreakdown() + BigDecimal::valueOf(this->_commonCause[j]->commonCause()));
            }
        }
        double time = i * totalTime / (count - 1);
        data->times.push_back(time);
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            op->initMarkovStatus(time);
        }
        this->GOGraph::calcAccumulativeProbability();
        if (this->getErrorMessage() != "")
        {
            delete data;
            return 0L;
        }
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[j];
            data->probabilities[j].push_back(op->accmulatives()->at(0)->probability(1).toString().toDouble());
        }
        // Fixed the error caused by common cause.
        for (int i = 0; i < this->_commonCause.size(); ++i)
        {
            QVector<double> r00;
            for (int j = 0; j < this->_commonCause[i]->operators()->size(); ++j)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[i]->operators()->at(j);
                op->markovStatus()->setFrequencyBreakdown(BigDecimal::valueOf("999999999"));
            }
            for (int j = 0; j < this->_operator.size(); ++j)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
                op->initMarkovStatus(time);
            }
            this->GOGraph::calcAccumulativeProbability();
            for (int j = 0; j < this->_operator.size(); ++j)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[j];
                r00.push_back(op->accmulatives()->at(0)->probability(1).toString().toDouble());
            }

            QVector<double> r11;
            for (int j = 0; j < this->_commonCause[i]->operators()->size(); ++j)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[i]->operators()->at(j);
                op->markovStatus()->setFrequencyBreakdown(BigDecimal::zero());
            }
            for (int j = 0; j < this->_operator.size(); ++j)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
                op->initMarkovStatus(time);
            }
            this->GOGraph::calcAccumulativeProbability();
            for (int j = 0; j < this->_operator.size(); ++j)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[j];
                r11.push_back(op->accmulatives()->at(0)->probability(1).toString().toDouble());
            }

            double miuSum = 0.0;
            for (int j = 0; j < this->_commonCause[i]->operators()->size(); ++j)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[i]->operators()->at(j);
                miuSum += op->markovStatus()->frequencyRepair().toString().toDouble();
            }
            double c = this->_commonCause[i]->commonCause();
            double c12 = miuSum / (c + miuSum) + (1 - miuSum / (c + miuSum)) * exp(-(c + miuSum) * time);
            c12 = 1 - c12;
            for (int j = 0; j < this->_operator.size(); ++j)
            {
                data->probabilities[j][i] += c12 * (r00[j] - r11[j]);
                if (data->probabilities[j][i] > 1.0)
                {
                    data->probabilities[j][i] = 1.0;
                }
            }
        }
        // Restore the lamda value.
        for (int i = 0; i < this->_operator.size(); ++i)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[i];
            op->markovStatus()->setFrequencyBreakdown(lamdas[i]);
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
            out << "<td>" << list[i]->status()->probability(j).toString() << "</td>";
            out << "</tr>" << endl;
        }
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyBreakdown().toString() << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyRepair().toString() << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Accumulative") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j < list[i]->accmulatives()->at(0)->number(); ++j)
        {
            out << "<tr>" << endl;
            out << QString("<td style='text-align:center;'>%1</td>").arg(j);
            out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j).toString() << "</td>";
            if (j == 0)
            {
                out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j).toString() << "</td>";
            }
            else
            {
                out << "<td>" << (list[i]->accmulatives()->at(0)->accumulative(j) - list[i]->accmulatives()->at(0)->accumulative(j - 1)).toString() << "</td>";
            }
            out << "</tr>" << endl;
        }
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown().toString() << "</td>";
        out << "<td>" << (BigDecimal::one() / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown()).toString() << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair().toString() << "</td>";
        out << "<td>" << (BigDecimal::one() / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair()).toString() << "</td>";
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
