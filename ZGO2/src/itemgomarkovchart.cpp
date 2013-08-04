#include <algorithm>
#include <qmath.h>
#include "itemgomarkovchart.h"
#include "itemarrow.h"
#include "definationeditorselectiontype.h"
#include "gomarkovchartdata.h"
using namespace std;

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
    this->_minP = 0.0;
    this->_maxP = 1.0;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_CHART);
    this->_displayIndex = 0;
    this->setIsDisplayP(true);
    this->setIsDisplayQ(true);
    this->setIsDisplayLambda(true);
    this->setIsDisplayMu(true);
}

ItemGOMarkovChart::~ItemGOMarkovChart()
{
    this->_time.clear();
    this->_P.clear();
}

void ItemGOMarkovChart::setTitle(const QString title)
{
    this->_title = title;
    this->update();
}

void ItemGOMarkovChart::setTime(QVector<double> time)
{
    this->_time.clear();
    this->_P.clear();
    for (int i = 0; i < time.size(); ++i)
    {
        this->_time.push_back(time.at(i));
    }
}

void ItemGOMarkovChart::setP(QVector<double> P)
{
    this->_P.clear();
    this->_maxP = 0.0;
    this->_minP = 1.0;
    this->_P.push_back(P[0]);
    for (int i = 1; i < P.size(); ++i)
    {
        if (isinf(P[i]) || isnan(P[i]))
        {
            P[i] = 1.0;
        }
        this->_P.push_back(P[i]);
        if (P[i] > this->_maxP)
        {
            this->_maxP = P[i];
        }
        if (P[i] < this->_minP)
        {
            this->_minP = P[i];
        }
    }
    if (this->_maxP == this->_minP)
    {
        this->_maxP = 1.0;
        this->_minP = 0.0;
    }
    this->update();
}

void ItemGOMarkovChart::setQ(QVector<double> Q)
{
    this->_Q.clear();
    this->_maxQ = 0.0;
    this->_minQ = 1.0;
    this->_Q.push_back(Q[0]);
    for (int i = 1; i < Q.size(); ++i)
    {
        if (isinf(Q[i]) || isnan(Q[i]))
        {
            Q[i] = 0.0;
        }
        this->_Q.push_back(1.0 - Q[i]);
        if (1.0 - Q[i] > this->_maxQ)
        {
            this->_maxQ = 1.0 - Q[i];
        }
        if (1.0 - Q[i] < this->_minQ)
        {
            this->_minQ = 1.0 - Q[i];
        }
    }
    if (this->_maxQ == this->_minQ)
    {
        this->_maxQ = 1.0;
        this->_minQ = 0.0;
    }
    this->update();
}

void ItemGOMarkovChart::setLambda(QVector<double> lambda)
{
    this->_lambda.clear();
    this->_maxLambda = 0.0;
    this->_minLambda = 1e100;
    this->_lambda.push_back(lambda[0]);
    for (int i = 1; i < lambda.size(); ++i)
    {
        if (isinf(lambda[i]) || isnan(lambda[i]))
        {
            lambda[i] = 0.0;
        }
        this->_lambda.push_back(lambda[i]);
        if (lambda[i] > this->_maxLambda)
        {
            this->_maxLambda = lambda[i];
        }
        if (lambda[i] < this->_minLambda)
        {
            this->_minLambda = lambda[i];
        }
    }
    if (this->_maxLambda == this->_minLambda)
    {
        this->_maxLambda *= 1.1;
        this->_minLambda /= 1.1;
    }
    this->update();
}

void ItemGOMarkovChart::setMu(QVector<double> mu)
{
    this->_mu.clear();
    this->_maxMu = 0.0;
    this->_minMu = 1e100;
    this->_mu.push_back(mu[0]);
    for (int i = 1; i < mu.size(); ++i)
    {
        if (isinf(mu[i]) || isnan(mu[i]))
        {
            mu[i] = 0.0;
        }
        this->_mu.push_back(mu[i]);
        if (mu[i] > this->_maxMu)
        {
            this->_maxMu = mu[i];
        }
        if (mu[i] < this->_minMu)
        {
            this->_minMu = mu[i];
        }
    }
    if (this->_maxMu == this->_minMu)
    {
        this->_maxMu *= 1.1;
        this->_minMu /= 1.2;
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

    if (this->isDisplayP())
    {
        painter->setPen(Qt::darkGreen);
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minP));
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxP));
        painter->drawText(QRectF(0, 0, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Normal Probability"));
    }
    else if (this->isDisplayQ())
    {
        painter->setPen(Qt::darkRed);
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minQ));
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxQ));
        painter->drawText(QRectF(0, 0, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Failure Probability"));
    }
    else if (this->isDisplayLambda())
    {
        painter->setPen(Qt::darkBlue);
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minLambda));
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxLambda));
        painter->drawText(QRectF(0, 0, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Lambda"));
    }
    else if (this->isDisplayMu())
    {
        painter->setPen(Qt::darkYellow);
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minMu));
        painter->drawText(QRectF(0, CHART_Y,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxMu));
        painter->drawText(QRectF(0, 0, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Mu"));
    }

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
    if (this->_time.size() == this->_P.size() && this->_time.size() > 0)
    {
        if (this->_detailIndex >= 0 && this->_detailIndex < this->_time.size())
        {
            painter->setPen(Qt::darkGray);
            if (this->isDisplayP())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxP - this->_P[this->_detailIndex]) / (this->_maxP - this->_minP);
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_P[this->_detailIndex]));
            }
            if (this->isDisplayQ())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxQ - this->_Q[this->_detailIndex]) / (this->_maxQ - this->_minQ);
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_P[this->_detailIndex]));
            }
            if (this->isDisplayLambda())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxLambda - this->_lambda[this->_detailIndex]) / (this->_maxLambda - this->_minLambda);
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_P[this->_detailIndex]));
            }
            if (this->isDisplayMu())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxMu - this->_mu[this->_detailIndex]) / (this->_maxMu - this->_minMu);
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_P[this->_detailIndex]));
            }
        }
        if (this->isDisplayP())
        {
            painter->setPen(Qt::darkGreen);
            painter->setBrush(Qt::darkGreen);
            QPen pen = painter->pen();
            pen.setWidth(LINE_WIDTH);
            painter->setPen(pen);
            float lastX = 0.0f;
            float lastY = 0.0f;
            for (int i = 1; i < this->_time.size(); ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxP - this->_P[i]) / (this->_maxP - this->_minP);
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
        }
        if (this->isDisplayQ())
        {
            painter->setPen(Qt::darkRed);
            painter->setBrush(Qt::darkRed);
            QPen pen = painter->pen();
            pen.setWidth(LINE_WIDTH);
            painter->setPen(pen);
            float lastX = 0.0f;
            float lastY = 0.0f;
            for (int i = 1; i < this->_time.size(); ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxQ - this->_Q[i]) / (this->_maxQ - this->_minQ);
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
        }
        if (this->isDisplayLambda())
        {
            painter->setPen(Qt::darkBlue);
            painter->setBrush(Qt::darkBlue);
            QPen pen = painter->pen();
            pen.setWidth(LINE_WIDTH);
            painter->setPen(pen);
            float lastX = 0.0f;
            float lastY = 0.0f;
            for (int i = 1; i < this->_time.size(); ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxLambda - this->_lambda[i]) / (this->_maxLambda - this->_minLambda);
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
        }
        if (this->isDisplayMu())
        {
            painter->setPen(Qt::darkYellow);
            painter->setBrush(Qt::darkYellow);
            QPen pen = painter->pen();
            pen.setWidth(LINE_WIDTH);
            painter->setPen(pen);
            float lastX = 0.0f;
            float lastY = 0.0f;
            for (int i = 1; i < this->_time.size(); ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_time.size() - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxMu - this->_mu[i]) / (this->_maxMu - this->_minMu);
                if (i > 1)
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
}

GOMarkovChartData *ItemGOMarkovChart::chartData() const
{
    return this->_chart;
}

void ItemGOMarkovChart::setChart(GOMarkovChartData *chart)
{
    this->_chart = chart;
}

bool ItemGOMarkovChart::isDisplayP() const
{
    return this->_isDisplayP;
}

bool ItemGOMarkovChart::isDisplayQ() const
{
    return this->_isDisplayQ;
}

bool ItemGOMarkovChart::isDisplayLambda() const
{
    return this->_isDisplayLambda;
}

bool ItemGOMarkovChart::isDisplayMu() const
{
    return this->_isDisplayMu;
}

void ItemGOMarkovChart::setIsDisplayP(const double value)
{
    this->_isDisplayP = value;
}

void ItemGOMarkovChart::setIsDisplayQ(const double value)
{
    this->_isDisplayQ = value;
}

void ItemGOMarkovChart::setIsDisplayLambda(const double value)
{
    this->_isDisplayLambda = value;
}

void ItemGOMarkovChart::setIsDisplayMu(const double value)
{
    this->_isDisplayMu = value;
}

int ItemGOMarkovChart::displayIndex() const
{
    return this->_displayIndex;
}

void ItemGOMarkovChart::setDisplayItem(int index)
{
    this->_detailIndex = index;
    this->setTitle(this->chartData()->names[index]);
    this->setP(this->chartData()->probabilities[index]);
    this->setQ(this->chartData()->probabilities[index]);
    this->setLambda(this->chartData()->lambdas[index]);
    this->setMu(this->chartData()->mus[index]);
}

void ItemGOMarkovChart::setDisplayItem(const QString name)
{
    for (int i = 0; i < this->chartData()->names.size(); ++i)
    {
        if (this->chartData()->names[i] == name)
        {
            this->setDisplayItem(i);
            break;
        }
    }
}
