#ifndef PARAMETERGOMARKOVCHART_H
#define PARAMETERGOMARKOVCHART_H
/**
 * The parameter for GO Markov Chart.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>
#include "parameterabstract.h"

class ParameterGOMarkovChart : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovChart(QWidget *parent = 0);
    void bindItem(void* item);

protected slots:
    void setDisplayItem(QString name);
    void setDisplayP(bool value);
    void setDisplayQ(bool value);
    void setDisplayLambda(bool value);
    void setDisplayMu(bool value);
};

#endif // PARAMETERGOMARKOVCHART_H
