#ifndef ITEMGOMARKOVCHART_H
#define ITEMGOMARKOVCHART_H
/**
 * The chart for displaying the result of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QList>
#include "itemdrawable.h"

class ItemArrow;

class ItemGOMarkovChart : public ItemDrawable
{
public:
    ItemGOMarkovChart(QGraphicsItem *parent = 0);
    ~ItemGOMarkovChart();
    void setTitle(const QString title);
    void setTime(QVector<double> time);
    void setProbability(QVector<double> probability);
    void setDetailIndex(float x, float y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

protected:
    QString _title;
    QList<double> _time;
    QList<double> _probability;
    ItemArrow *_xAxis;
    ItemArrow *_yAxis;
    double _maxProbability;
    double _minProbability;
    int _detailIndex;
};

#endif // ITEMGOMARKOVCHART_H
