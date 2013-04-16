#include <QFile>
#include <QDomDocument>
#include "gomarkovchartdata.h"

GOMarkovChartData::~GOMarkovChartData()
{
    this->ids.clear();
    this->types.clear();
    this->times.clear();
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        this->probabilities[i].clear();
    }
    this->probabilities.clear();
    for (int i = 0; i < this->lamdaResults.size(); ++i)
    {
        this->lamdaResults[i].clear();
    }
    this->lamdaResults.clear();
    for (int i = 0; i < this->miuResults.size(); ++i)
    {
        this->miuResults[i].clear();
    }
    this->miuResults.clear();
}

bool GOMarkovChartData::save(QString fileName)
{
    QDomDocument document;
    QDomElement root = document.createElement("GO_Markov_Data");
    root.setAttribute("support", "ZHG");
    document.appendChild(root);
    QDomElement partRoot = document.createElement("ids");
    for (int i = 0; i < this->ids.size(); ++i)
    {
        QDomElement element = document.createElement("id");
        element.setAttribute("value", this->ids[i]);
        partRoot.appendChild(element);
    }
    root.appendChild(partRoot);
    partRoot = document.createElement("types");
    for (int i = 0; i < this->types.size(); ++i)
    {
        QDomElement element = document.createElement("type");
        element.setAttribute("value", this->types[i]);
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
    partRoot = document.createElement("lamdas");
    for (int i = 0; i < this->lamdaResults.size(); ++i)
    {
        QDomElement partElement = document.createElement("lamda");
        for (int j = 0; j < this->lamdaResults[i].size(); ++j)
        {
            QDomElement element = document.createElement("lamda");
            element.setAttribute("value", this->lamdaResults[i][j]);
            partElement.appendChild(element);
        }
        partRoot.appendChild(partElement);
    }
    root.appendChild(partRoot);
    partRoot = document.createElement("mius");
    for (int i = 0; i < this->miuResults.size(); ++i)
    {
        QDomElement partElement = document.createElement("miu");
        for (int j = 0; j < this->miuResults[i].size(); ++j)
        {
            QDomElement element = document.createElement("miu");
            element.setAttribute("value", this->miuResults[i][j]);
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
        this->ids.push_back(element.attribute("value").toInt());
    }
    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element = partRoot.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->types.push_back(element.attribute("value").toInt());
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
    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element1 = partRoot.firstChildElement(); !element1.isNull(); element1 = element1.nextSiblingElement())
    {
        this->lamdaResults.push_back(QVector<double>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            this->lamdaResults[this->lamdaResults.size() - 1].push_back(element2.attribute("value").toDouble());
        }
    }
    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element1 = partRoot.firstChildElement(); !element1.isNull(); element1 = element1.nextSiblingElement())
    {
        this->miuResults.push_back(QVector<double>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            this->miuResults[this->miuResults.size() - 1].push_back(element2.attribute("value").toDouble());
        }
    }
    return true;
}
