#ifndef GOMARKOVCHARTDATA_H
#define GOMARKOVCHARTDATA_H
#include <QVector>
#include "doublevector.h"

class GOMarkovChartData
{
public:
    QVector<QString> names;
    QVector<double> times;
    QVector<QVector<DoubleVector> > probabilities;
    QVector<QVector<DoubleVector> > lambdas;
    QVector<QVector<DoubleVector> > mus;
    virtual ~GOMarkovChartData();
    bool save(QString fileName);
    bool tryOpen(QString fileName);
    bool saveAsHTML(QString fileName);
};

#endif // GOMARKOVCHARTDATA_H
