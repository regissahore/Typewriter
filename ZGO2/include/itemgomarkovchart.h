#ifndef ITEMGOMARKOVCHART_H
#define ITEMGOMARKOVCHART_H
/**
 * The chart for displaying the result of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QList>
#include "itemdrawable.h"

class ItemArrow;
class GOMarkovChartData;

class ItemGOMarkovChart : public ItemDrawable
{
public:
    ItemGOMarkovChart(QGraphicsItem *parent = 0);
    ~ItemGOMarkovChart();
    void setTitle(const QString title);
    void setTime(QVector<double> time);
    void setP(QVector<double> P);
    void setQ(QVector<double> Q);
    void setLambda(QVector<double> lambda);
    void setMu(QVector<double> mu);
    void setDetailIndex(float x, float y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GOMarkovChartData *chartData() const;
    void setChart(GOMarkovChartData *chartData);
    bool isDisplayP() const;
    bool isDisplayQ() const;
    bool isDisplayLambda() const;
    bool isDisplayMu() const;
    void setIsDisplayP(const double value);
    void setIsDisplayQ(const double value);
    void setIsDisplayLambda(const double value);
    void setIsDisplayMu(const double value);
    int chartNum() const;
    int totalHeight() const;
    int displayIndex() const;
    void setDisplayItem(int index);
    void setDisplayItem(const QString name);

protected:
    QString _title;
    QList<double> _time;
    QList<double> _P;
    QList<double> _Q;
    QList<double> _lambda;
    QList<double> _mu;
    ItemArrow *_xAxis[4];
    ItemArrow *_yAxis[4];
    double _maxP;
    double _minP;
    double _maxQ;
    double _minQ;
    double _maxLambda;
    double _minLambda;
    double _maxMu;
    double _minMu;
    int _detailIndex;
    GOMarkovChartData *_chart;
    bool _isDisplayP;
    bool _isDisplayQ;
    bool _isDisplayLambda;
    bool _isDisplayMu;
    int _displayIndex;
};

#endif // ITEMGOMARKOVCHART_H
