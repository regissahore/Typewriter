#ifndef ITEMGOMARKOVCHART_H
#define ITEMGOMARKOVCHART_H
#include <QList>
#include "itemdrawable.h"
#include "doublevector.h"

class ItemArrow;
class GOMarkovChartData;

class ItemGOMarkovChart : public ItemDrawable
{
public:
    ItemGOMarkovChart(QGraphicsItem *parent = 0);
    ~ItemGOMarkovChart();
    void setTitle(const QString title);
    void setTime(QVector<double> time);
    void setP(QVector<DoubleVector> P);
    void setQ(QVector<DoubleVector> Q);
    void setLambda(QVector<DoubleVector> lambda);
    void setMu(QVector<DoubleVector> mu);
    void setDetailIndex(float x, float y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GOMarkovChartData *chartData() const;
    void setChart(GOMarkovChartData *chartData);
    bool isDisplayP() const;
    bool isDisplayQ() const;
    bool isDisplayLambda() const;
    bool isDisplayMu() const;
    void setIsDisplayP(const bool value);
    void setIsDisplayQ(const bool value);
    void setIsDisplayLambda(const bool value);
    void setIsDisplayMu(const bool value);
    int chartNum() const;
    int totalHeight() const;
    int displayIndex() const;
    void setDisplayItem(int index, int vectorIndex = 0);
    void setDisplayItem(const QString name, int vectorIndex = 0);
    int displayVectorIndex() const;
    void setDisplayVectorIndex(const int index);

protected:
    QString _title;
    QList<double> _time;
    QList<DoubleVector> _P;
    QList<DoubleVector> _Q;
    QList<DoubleVector> _lambda;
    QList<DoubleVector> _mu;
    ItemArrow *_xAxis[4];
    ItemArrow *_yAxis[4];
    DoubleVector _maxP;
    DoubleVector _minP;
    DoubleVector _maxQ;
    DoubleVector _minQ;
    DoubleVector _maxLambda;
    DoubleVector _minLambda;
    DoubleVector _maxMu;
    DoubleVector _minMu;
    int _detailIndex;
    GOMarkovChartData *_chart;
    bool _isDisplayP;
    bool _isDisplayQ;
    bool _isDisplayLambda;
    bool _isDisplayMu;
    int _displayIndex;
    int _displayVectorIndex;
    int _displayTime;
};

#endif // ITEMGOMARKOVCHART_H
