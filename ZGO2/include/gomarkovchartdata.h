#ifndef GOMARKOVCHARTDATA_H
#define GOMARKOVCHARTDATA_H
/**
 * The record of markov analysis result.
 * @author ZHG <CyberZHG@gmail.com>
 */
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
