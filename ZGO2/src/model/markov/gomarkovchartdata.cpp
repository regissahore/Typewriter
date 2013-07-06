#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include "gomarkovchartdata.h"
#include "gooperator.h"

GOMarkovChartData::~GOMarkovChartData()
{
    this->names.clear();
    this->times.clear();
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        this->probabilities[i].clear();
    }
    this->probabilities.clear();
}

bool GOMarkovChartData::save(QString fileName)
{
    QDomDocument document;
    QDomElement root = document.createElement("GO_Markov_Data");
    root.setAttribute("support", "ZHG");
    document.appendChild(root);
    QDomElement partRoot = document.createElement("names");
    for (int i = 0; i < this->names.size(); ++i)
    {
        QDomElement element = document.createElement("name");
        element.setAttribute("value", this->names[i]);
        partRoot.appendChild(element);
    }
    root.appendChild(partRoot);
    partRoot = document.createElement("times");
    for (int i = 0; i < this->times.size(); ++i)
    {
        QDomElement element = document.createElement("time");
        element.setAttribute("value", this->times[i]);
        partRoot.appendChild(element);
    }
    root.appendChild(partRoot);
    partRoot = document.createElement("probabilities");
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        QDomElement partElement = document.createElement("probability");
        for (int j = 0; j < this->probabilities[i].size(); ++j)
        {
            QDomElement element = document.createElement("probability");
            element.setAttribute("value", this->probabilities[i][j]);
            partElement.appendChild(element);
        }
        partRoot.appendChild(partElement);
    }
    root.appendChild(partRoot);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    file.write(document.toByteArray(4));
    file.flush();
    file.close();
    return true;
}

bool GOMarkovChartData::tryOpen(QString fileName)
{
    QDomDocument document;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    QDomElement root = document.firstChildElement();
    if (root.isNull())
    {
        return false;
    }
    if (root.attribute("support") != "ZHG")
    {
        return false;
    }
    QDomElement partRoot = root.firstChildElement();
    if (document.isNull())
    {
        return false;
    }
    for (QDomElement element = partRoot.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->names.push_back(element.attribute("value"));
    }
    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element = partRoot.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->times.push_back(element.attribute("value").toDouble());
    }
    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element1 = partRoot.firstChildElement(); !element1.isNull(); element1 = element1.nextSiblingElement())
    {
        this->probabilities.push_back(QVector<double>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            this->probabilities[this->probabilities.size() - 1].push_back(element2.attribute("value").toDouble());
        }
    }
    return true;
}

bool GOMarkovChartData::saveAsHTML(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
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
    out << "<h1>" + QObject::tr("Analysis Result") + "</h1>" << endl;
    out << "<table>" << endl;
    out << "<tr style='text-align: center;'>" << endl;
    out << "<th>" + QObject::tr("Time") + "</th>" << endl;
    for (int i = 0; i < names.size(); ++i)
    {
        out << "<th>" << names[i] << "</th>" << endl;
    }
    out << "</tr>" << endl;
    for (int i = 0; i < times.size(); ++i)
    {
        out << "<tr>" << endl;
        out << "<td>" << times[i] << "</td>" << endl;
        for (int j = 0; j < names.size(); ++j)
        {
            out << "<td>" << probabilities[j][i] << "</td>" << endl;
        }
        out << "</tr>" << endl;
    }
    out << "</table>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}
