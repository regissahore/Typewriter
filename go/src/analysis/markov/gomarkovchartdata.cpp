#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include "GoMarkovChartData.h"
#include "GoOperator.h"

GoMarkovChartData::~GoMarkovChartData()
{
    this->names.clear();
    this->times.clear();
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        this->probabilities[i].clear();
    }
    this->probabilities.clear();
}
bool GoMarkovChartData::save(QString fileName)
{
    QDomDocument document;
    QDomElement root = document.createElement("Go_Markov_Data");
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
            element.setAttribute("length", this->probabilities[i][j].length());
            for (int k = 0; k < probabilities[i][j].length(); ++k)
            {
                element.setAttribute(QString("value_%1").arg(k), this->probabilities[i][j].toString(k));
            }
            partElement.appendChild(element);
        }
        partRoot.appendChild(partElement);
    }
    root.appendChild(partRoot);

    partRoot = document.createElement("lambdas");
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        QDomElement partElement = document.createElement("lambdas");
        for (int j = 0; j < this->lambdas[i].size(); ++j)
        {
            QDomElement element = document.createElement("lambdas");
            element.setAttribute("length", this->lambdas[i][j].length());
            for (int k = 0; k < lambdas[i][j].length(); ++k)
            {
                element.setAttribute(QString("value_%1").arg(k), this->lambdas[i][j].toString(k));
            }
            partElement.appendChild(element);
        }
        partRoot.appendChild(partElement);
    }
    root.appendChild(partRoot);

    partRoot = document.createElement("mus");
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        QDomElement partElement = document.createElement("mus");
        for (int j = 0; j < this->mus[i].size(); ++j)
        {
            QDomElement element = document.createElement("mus");
            element.setAttribute("length", this->mus[i][j].length());
            for (int k = 0; k < mus[i][j].length(); ++k)
            {
                element.setAttribute(QString("value_%1").arg(k), this->mus[i][j].toString(k));
            }
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

bool GoMarkovChartData::tryOpen(QString fileName)
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
        this->probabilities.push_back(QVector<DoubleVector>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            DoubleVector vector;
            vector.setLength(element2.attribute("length").toInt());
            for (int i = 0; i < vector.length(); ++i)
            {
                vector.setValue(i, element2.attribute(QString("value_%1").arg(i)).toDouble());
            }
            this->probabilities[this->probabilities.size() - 1].push_back(vector);
        }
    }

    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element1 = partRoot.firstChildElement(); !element1.isNull(); element1 = element1.nextSiblingElement())
    {
        this->lambdas.push_back(QVector<DoubleVector>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            DoubleVector vector;
            vector.setLength(element2.attribute("length").toInt());
            for (int i = 0; i < vector.length(); ++i)
            {
                vector.setValue(i, element2.attribute(QString("value_%1").arg(i)).toDouble());
            }
            this->lambdas[this->lambdas.size() - 1].push_back(vector);
        }
    }

    partRoot = partRoot.nextSiblingElement();
    for (QDomElement element1 = partRoot.firstChildElement(); !element1.isNull(); element1 = element1.nextSiblingElement())
    {
        this->mus.push_back(QVector<DoubleVector>());
        for (QDomElement element2 = element1.firstChildElement(); !element2.isNull(); element2 = element2.nextSiblingElement())
        {
            DoubleVector vector;
            vector.setLength(element2.attribute("length").toInt());
            for (int i = 0; i < vector.length(); ++i)
            {
                vector.setValue(i, element2.attribute(QString("value_%1").arg(i)).toDouble());
            }
            this->mus[this->mus.size() - 1].push_back(vector);
        }
    }

    return true;
}

bool GoMarkovChartData::saveAsHTML(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");

    QFile headFile("js/compress_page_analysis_head.html");
    if (!headFile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QTextStream head(&headFile);
    head.setCodec("UTF-8");
    out << head.readAll();
    headFile.close();

    out << "var data = {";
    out << "names: [";
    for (int i = 0; i < this->names.size(); ++i)
    {
        if (i)
        {
            out << ", ";
        }
        out << "'" + this->names[i] + "'";
    }
    out << "], times: [";
    for (int i = 0; i < this->times.size(); ++i)
    {
        if (i)
        {
            out << ", ";
        }
        out << this->times[i];
    }
    out << "], ps: [";
    for (int i = 0; i < this->probabilities.size(); ++i)
    {
        if (i)
        {
            out << ", ";
        }
        out << "[";
        for (int j = 0; j < this->probabilities[i][0].length(); ++j)
        {
            if (j)
            {
                out << ", ";
            }
            out << "[";
            for (int k = 0; k < this->probabilities[i].size(); ++k)
            {
                if (k)
                {
                    out << ", ";
                }
                out << this->probabilities[i][k].getValue(j);
            }
            out << "]";
        }
        out << "]";
    }
    out << "], lambdas: [";
    for (int i = 0; i < this->lambdas.size(); ++i)
    {
        if (i)
        {
            out << ", ";
        }
        out << "[";
        for (int j = 0; j < this->lambdas[i][0].length(); ++j)
        {
            if (j)
            {
                out << ", ";
            }
            out << "[";
            for (int k = 0; k < this->lambdas[i].size(); ++k)
            {
                if (k)
                {
                    out << ", ";
                }
                out << this->lambdas[i][k].getValue(j);
            }
            out << "]";
        }
        out << "]";
    }
    out << "],";
    out << "};";

    QFile tailFile("js/compress_page_analysis_tail.html");
    if (!tailFile.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QTextStream tail(&tailFile);
    tail.setCodec("UTF-8");
    out << tail.readAll();
    tailFile.close();

    file.close();
    return true;
}
