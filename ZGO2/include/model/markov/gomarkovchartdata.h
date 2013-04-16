#ifndef GOMARKOVCHARTDATA_H
#define GOMARKOVCHARTDATA_H
/**
 * The record of markov analysis result.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOMarkovChartData
{
public:
    QVector<int> types;
    QVector<int> ids;
    QVector<double> times;
    QVector<QVector<double> > probabilities;
    QVector<QVector<double> > lamdaResults;
    QVector<QVector<double> > miuResults;
    virtual ~GOMarkovChartData();
    bool save(QString fileName);
    bool tryOpen(QString fileName);
};

#endif // GOMARKOVCHARTDATA_H
