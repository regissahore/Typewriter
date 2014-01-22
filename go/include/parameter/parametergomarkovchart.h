#ifndef PARAMETERGOMARKOVCHART_H
#define PARAMETERGOMARKOVCHART_H
#include <QObject>
#include "ParameterAbstract.h"

class QSpinBox;

class ParameterGoMarkovChart : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGoMarkovChart(QWidget *parent = 0);
    void bindItem(void* item);

protected:
    QSpinBox *_spinVector;

protected slots:
    void setDisplayItem(QString name);
    void setDisplayVectorIndex(int index);
    void setDisplayP(bool value);
    void setDisplayQ(bool value);
    void setDisplayLambda(bool value);
    void setDisplayMu(bool value);
};

#endif // PARAMETERGOMARKOVCHART_H
