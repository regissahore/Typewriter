#include <qmath.h>
#include "itemgomarkovchart.h"
#include "itemarrow.h"

const int ITEM_WIDTH = 800;
const int ITEM_HEIGHT = 600;
const int CHART_X = 100;
const int CHART_Y = 100;
const int CHART_WIDTH = 600;
const int CHART_HEIGHT = 400;
const int TEXT_MARGIN = 10;
const int LINE_WIDTH = 2;

ItemGOMarkovChart::ItemGOMarkovChart(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->_xAxis = new ItemArrow(this);
    this->_xAxis->setPos(CHART_X, CHART_Y + CHART_HEIGHT);
    this->_xAxis->setEnd(0, - CHART_HEIGHT);
    this->_yAxis = new ItemArrow(this);
    this->_yAxis->setPos(CHART_X, CHART_Y + CHART_HEIGHT);
    this->_yAxis->setEnd(CHART_WIDTH, 0);
    this->setColor(Qt::darkGreen);
    this->_detailIndex = 0;
    this->_minProbability = 0.0;
    this->_maxProbability = 1.0;
}

ItemGOMarkovChart::~ItemGOMarkovChart()
{
    this->_time.clear();
    this->_probability.clear();
}

void ItemGOMarkovChart::setTitle(const QString title)
{
    this->_title = title;
    this->update();
}

void ItemGOMarkovChart::setTime(QVector<double> time)
{
    this->_time.clear();
    this->_probability.clear();
    for (int i = 0; i < time.size(); ++i)
    {
        this->_time.push_back(time.at(i));
    }
}

void ItemGOMarkovChart::setProbability(QVector<double> probability)
{
    this->_probability.clear();
    this->_maxProbability = 0.0;
    this->_minProbability = 1.0;
    probability[0] = 1.0;
    for (int i = 0; i < probability.size(); ++i)
    {
        if (isinf(probability[i]) || isnan(probability[i]))
        {
            probability[i] = 1.0;
        }
        this->_probability.push_back(probability[i]);
        if (probability[i] > this->_maxProbability)
        {
            this->_maxProbability = probability[i];
        }
        if (probability[i] < this->_minProbability)
        {
            this->_minProbability = probability[i];
        }
    }
    if (this->_maxProbability == this->_minProbability)
    {
        this->_maxProbability = 1.0;
        this->_minProbability = 0.0;
    }
    this->update();
}

void ItemGOMarkovChart::setDetailIndex(float x, float y)
{
    x -= this->x();
    y -= this->y();
    if (x >= CHART_X && x <= ITEM_WIDTH)
    {
        if (y >= 0 && y <= ITEM_HEIGHT)
        {
            float xStep = 1.0f * CHART_WIDTH / this->_time.size();
            this->_detailIndex = floor((x - CHART_X) / xStep);
            if (this->_detailIndex >= this->_time.size())
            {
                this->_detailIndex = this->_time.size() - 1;
            }
            this->update();
        }
    }
}

QRectF ItemGOMarkovChart::boundingRect() const
{
    return QRectF(0, 0, ITEM_WIDTH, ITEM_HEIGHT);
}

void ItemGOMarkovChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawText(QRectF(0, 0, ITEM_WIDTH, CHART_Y),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      this->_title);

    painter->drawText(QRectF(0, CHART_Y,
                             CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                      Qt::AlignRight | Qt::AlignBottom,
                      QString("%1").arg(this->_minProbability));
    painter->drawText(QRectF(0, CHART_Y,
                             CHART_X - TEXT_MARGIN, CHART_Y),
                      Qt::AlignRight | Qt::AlignTop,
                      QString("%1").arg(this->_maxProbability));
    painter->drawText(QRectF(0, 0, CHART_X, CHART_Y - TEXT_MARGIN),
                      Qt::AlignRight | Qt::AlignBottom,
                      QObject::tr("Probability"));

    if (this->_time.size() > 1)
    {
        painter->drawText(QRectF(CHART_X,
                                 CHART_Y + CHART_HEIGHT + TEXT_MARGIN,
                                 CHART_WIDTH,
                                 ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                          Qt::AlignLeft | Qt::AlignTop,
                          QString("%1").arg(this->_time.at(0)));
        painter->drawText(QRectF(CHART_X, CHART_Y + CHART_HEIGHT + TEXT_MARGIN,
                             CHART_WIDTH, ITEM_HEIGHT - CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_time.at(this->_time.size() - 1)));
    }
    painter->drawText(QRectF(CHART_X + CHART_WIDTH + TEXT_MARGIN,
                             CHART_Y + CHART_HEIGHT,
                             ITEM_WIDTH - CHART_WIDTH - CHART_X,
                             ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                      Qt::AlignLeft | Qt::AlignTop,
                      QObject::tr("Time"));
    if (this->_time.size() == this->_probability.size() && this->_time.size() > 0)
    {
        if (this->_detailIndex >= 0 && this->_detailIndex < this->_time.size())
        {
            painter->setPen(Qt::darkGray);
            float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_time.size() - 1);
            float y = CHART_Y + CHART_HEIGHT * (this->_maxProbability - this->_probability[this->_detailIndex]) / (this->_maxProbability - this->_minProbability);
            painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
            painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT), QPointF(x, y));
            painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                     300, 300),
                              Qt::AlignLeft | Qt::AlignBottom,
                              QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_probability[this->_detailIndex]));
        }
        painter->setPen(this->_color);
        painter->setBrush(this->_color);
        QPen pen = painter->pen();
        pen.setWidth(LINE_WIDTH);
        painter->setPen(pen);
        float lastX = 0.0f;
        float lastY = 0.0f;
        for (int i = 0; i < this->_time.size(); ++i)
        {
            float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_time.size() - 1);
            float y = CHART_Y + CHART_HEIGHT * (this->_maxProbability - this->_probability[i]) / (this->_maxProbability - this->_minProbability);
            if (i > 0)
            {
                painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
            }
            lastX = x;
            lastY = y;
        }
        pen.setWidth(1);
        painter->setPen(pen);
    }
}
