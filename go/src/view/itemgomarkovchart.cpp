#include <algorithm>
#include <qmath.h>
#include "ItemGoMarkovChart.h"
#include "ItemArrow.h"
#include "DefinationEditorSelectionType.h"
#include "GoMarkovChartData.h"
#include "DoubleVector.h"
using namespace std;

const int ITEM_WIDTH = 800;
const int ITEM_HEIGHT = 450;
const int ITEM_SPACING = 10;
const int CHART_X = 100;
const int CHART_Y = 100;
const int CHART_WIDTH = 600;
const int CHART_HEIGHT = 400;
const int TEXT_MARGIN = 10;
const int LINE_WIDTH = 2;

ItemGoMarkovChart::ItemGoMarkovChart(QGraphicsItem *parent) : ItemDrawable(parent)
{
    int shiftY = 0;
    for (int i = 0; i < 4; ++i)
    {
        this->_xAxis[i] = new ItemArrow(this);
        this->_xAxis[i]->setPos(CHART_X, CHART_Y + CHART_HEIGHT + shiftY);
        this->_xAxis[i]->setEnd(0, - CHART_HEIGHT);
        this->_yAxis[i] = new ItemArrow(this);
        this->_yAxis[i]->setPos(CHART_X, CHART_Y + CHART_HEIGHT + shiftY);
        this->_yAxis[i]->setEnd(CHART_WIDTH, 0);
        shiftY += ITEM_HEIGHT + ITEM_SPACING;
    }
    this->setColor(Qt::darkGreen);
    this->_detailIndex = 0;
    this->_minP = 0.0;
    this->_maxP = 1.0;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_CHART);
    this->_displayIndex = 0;
    this->_displayVectorIndex = 0;
    this->setIsDisplayP(true);
    this->setIsDisplayQ(true);
    this->setIsDisplayLambda(true);
    this->setIsDisplayMu(true);
}

ItemGoMarkovChart::~ItemGoMarkovChart()
{
    this->_time.clear();
    this->_P.clear();
}

void ItemGoMarkovChart::setTitle(const QString title)
{
    this->_title = title;
    this->update();
}

void ItemGoMarkovChart::setTime(QVector<double> time)
{
    this->_time.clear();
    this->_P.clear();
    for (int i = 0; i < time.size(); ++i)
    {
        this->_time.push_back(time.at(i));
    }
}

void ItemGoMarkovChart::setP(QVector<DoubleVector> P)
{
    int vectorIndex = this->displayVectorIndex();
    this->_P.clear();
    this->_maxP = 0.0;
    this->_minP = 1.0;
    this->_P.push_back(P[0].getValue(vectorIndex));
    for (int i = 1; i < P.size(); ++i)
    {
        if (isinf(P[i].getValue(vectorIndex)) || isnan(P[i].getValue(vectorIndex)))
        {
            P[i].setValue(vectorIndex, 1.0);
        }
        this->_P.push_back(P[i].getValue(vectorIndex));
        if (P[i].getValue(vectorIndex) > this->_maxP)
        {
            this->_maxP = P[i].getValue(vectorIndex);
        }
        if (P[i].getValue(vectorIndex) < this->_minP)
        {
            this->_minP = P[i].getValue(vectorIndex);
        }
    }
    if (this->_maxP - this->_minP < 1e-9)
    {
        this->_maxP += this->_maxP;
        if (this->_maxP > 1.0)
        {
            this->_maxP = 1.0;
        }
        this->_minP = 0.0;
    }
    for (this->_displayTime = this->_time.size() - 1; this->_displayTime > 0; --this->_displayTime)
    {
        bool flag = false;
        for (int i = 0 ; i < this->_P[this->_displayTime].length(); ++i)
        {
            if (fabs(this->_P[this->_displayTime].getValue(i) - this->_P[this->_displayTime - 1].getValue(i)) >  1e-9)
            {
                flag = true;
            }
        }
        if (flag)
        {
            break;
        }
    }
    this->_displayTime += 20;
    if (this->_displayTime > this->_time.size())
    {
        this->_displayTime = this->_time.size();
    }
    this->update();
}

void ItemGoMarkovChart::setQ(QVector<DoubleVector> Q)
{
    int vectorIndex = this->displayVectorIndex();
    this->_Q.clear();
    this->_maxQ = 0.0;
    this->_minQ = 1.0;
    this->_Q.push_back(Q[0].getValue(vectorIndex));
    for (int i = 1; i < Q.size(); ++i)
    {
        if (isinf(Q[i].getValue(vectorIndex)) || isnan(Q[i].getValue(vectorIndex)))
        {
            Q[i].setValue(vectorIndex, 0.0);
        }
        this->_Q.push_back(1.0 - Q[i].getValue(vectorIndex));
        if ((1.0 - Q[i]).getValue(vectorIndex) > this->_maxQ)
        {
            this->_maxQ = (1.0 - Q[i]).getValue(vectorIndex);
        }
        if ((1.0 - Q[i]).getValue(vectorIndex) < this->_minQ)
        {
            this->_minQ = (1.0 - Q[i]).getValue(vectorIndex);
        }
    }
    if (this->_maxQ - this->_minQ < 1e-9)
    {
        this->_maxQ += this->_maxQ;
        if (this->_maxQ > 1.0)
        {
            this->_maxQ = 1.0;
        }
        this->_minQ = 0.0;
    }
    this->update();
}

void ItemGoMarkovChart::setLambda(QVector<DoubleVector> lambda)
{
    int vectorIndex = this->displayVectorIndex();
    this->_lambda.clear();
    this->_maxLambda = 0.0;
    this->_minLambda = 1e100;
    this->_lambda.push_back(lambda[0].getValue(vectorIndex));
    for (int i = 1; i < lambda.size(); ++i)
    {
        if (isinf(lambda[i].getValue(vectorIndex)) || isnan(lambda[i].getValue(vectorIndex)))
        {
            lambda[i].setValue(vectorIndex, 0.0);
        }
        this->_lambda.push_back(lambda[i].getValue(vectorIndex));
        if (lambda[i].getValue(vectorIndex) > this->_maxLambda)
        {
            this->_maxLambda = lambda[i].getValue(vectorIndex);
        }
        if (lambda[i].getValue(vectorIndex) < this->_minLambda)
        {
            this->_minLambda = lambda[i].getValue(vectorIndex);
        }
    }
    if (this->_maxLambda - this->_minLambda < 1e-9)
    {
        this->_maxLambda += this->_maxLambda;
        this->_minLambda  = 0.0;
    }
    this->update();
}

void ItemGoMarkovChart::setMu(QVector<DoubleVector> mu)
{
    int vectorIndex = this->displayVectorIndex();
    this->_mu.clear();
    this->_maxMu = 0.0;
    this->_minMu = 1e100;
    this->_mu.push_back(mu[0].getValue(vectorIndex));
    for (int i = 1; i < mu.size(); ++i)
    {
        if (isinf(mu[i].getValue(vectorIndex)) || isnan(mu[i].getValue(vectorIndex)))
        {
            mu[i].setValue(vectorIndex, 0.0);
        }
        this->_mu.push_back(mu[i].getValue(vectorIndex));
        if (mu[i].getValue(vectorIndex) > this->_maxMu)
        {
            this->_maxMu = mu[i].getValue(vectorIndex);
        }
        if (mu[i].getValue(vectorIndex) < this->_minMu)
        {
            this->_minMu = mu[i].getValue(vectorIndex);
        }
    }
    if (this->_maxMu - this->_minMu < 1e-9)
    {
        this->_maxMu += this->_maxMu;
        this->_minMu = 0.0;
    }
    this->update();
}

void ItemGoMarkovChart::setDetailIndex(float x, float y)
{
    x -= this->x();
    y -= this->y();
    if (x >= CHART_X && x <= ITEM_WIDTH)
    {
        if (y >= 0 && y <= this->totalHeight())
        {
            float xStep = 1.0f * CHART_WIDTH / this->_displayTime;
            this->_detailIndex = floor((x - CHART_X) / xStep);
            if (this->_detailIndex >= this->_displayTime)
            {
                this->_detailIndex = this->_displayTime - 1;
            }
            this->update();
        }
    }
}

QRectF ItemGoMarkovChart::boundingRect() const
{
    return QRectF(0, 0, ITEM_WIDTH, this->totalHeight());
}

void ItemGoMarkovChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    for (int i = 0; i < this->chartNum(); ++i)
    {
        this->_xAxis[i]->setVisible(true);
        this->_yAxis[i]->setVisible(true);
    }
    for (int i = this->chartNum(); i < 4; ++i)
    {
        this->_xAxis[i]->setVisible(false);
        this->_yAxis[i]->setVisible(false);
    }

    int shiftY = 0;
    if (this->isDisplayP())
    {
        painter->setPen(Qt::darkGreen);
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minP.toString(0)));
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxP.toString(0)));
        painter->drawText(QRectF(0, shiftY, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Normal Probability"));
        shiftY += ITEM_HEIGHT + ITEM_SPACING;
    }
    if (this->isDisplayQ())
    {
        painter->setPen(Qt::darkRed);
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minQ.toString(0)));
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxQ.toString(0)));
        painter->drawText(QRectF(0, shiftY, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Failure Probability"));
        shiftY += ITEM_HEIGHT + ITEM_SPACING;
    }
    if (this->isDisplayLambda())
    {
        painter->setPen(Qt::darkBlue);
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minLambda.toString(0)));
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxLambda.toString(0)));
        painter->drawText(QRectF(0, shiftY, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Lambda"));
        shiftY += ITEM_HEIGHT + ITEM_SPACING;
    }
    if (this->isDisplayMu())
    {
        painter->setPen(Qt::darkYellow);
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_HEIGHT),
                          Qt::AlignRight | Qt::AlignBottom,
                          QString("%1").arg(this->_minMu.toString(0)));
        painter->drawText(QRectF(0, CHART_Y + shiftY,
                                 CHART_X - TEXT_MARGIN, CHART_Y),
                          Qt::AlignRight | Qt::AlignTop,
                          QString("%1").arg(this->_maxMu.toString(0)));
        painter->drawText(QRectF(0, shiftY, CHART_X, CHART_Y - TEXT_MARGIN),
                          Qt::AlignRight | Qt::AlignBottom,
                          QObject::tr("Mu"));
        shiftY += ITEM_HEIGHT + ITEM_SPACING;
    }

    if (this->_time.size() > 1)
    {
        shiftY = 0;
        if (this->isDisplayP())
        {
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(0)));
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT),
                              Qt::AlignRight | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(this->_displayTime - 1)));
            painter->drawText(QRectF(CHART_X + CHART_WIDTH + TEXT_MARGIN,
                                     CHART_Y + CHART_HEIGHT + shiftY,
                                     ITEM_WIDTH - CHART_WIDTH - CHART_X,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QObject::tr("Time"));
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
        }
        if (this->isDisplayQ())
        {
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(0)));
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT),
                              Qt::AlignRight | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(this->_displayTime - 1)));
            painter->drawText(QRectF(CHART_X + CHART_WIDTH + TEXT_MARGIN,
                                     CHART_Y + CHART_HEIGHT + shiftY,
                                     ITEM_WIDTH - CHART_WIDTH - CHART_X,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QObject::tr("Time"));
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
        }
        if (this->isDisplayLambda())
        {
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(0)));
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT),
                              Qt::AlignRight | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(this->_displayTime - 1)));
            painter->drawText(QRectF(CHART_X + CHART_WIDTH + TEXT_MARGIN,
                                     CHART_Y + CHART_HEIGHT + shiftY,
                                     ITEM_WIDTH - CHART_WIDTH - CHART_X,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QObject::tr("Time"));
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
        }
        if (this->isDisplayMu())
        {
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(0)));
            painter->drawText(QRectF(CHART_X,
                                     CHART_Y + CHART_HEIGHT + TEXT_MARGIN + shiftY,
                                     CHART_WIDTH,
                                     ITEM_HEIGHT - CHART_HEIGHT),
                              Qt::AlignRight | Qt::AlignTop,
                              QString("%1").arg(this->_time.at(this->_displayTime - 1)));
            painter->drawText(QRectF(CHART_X + CHART_WIDTH + TEXT_MARGIN,
                                     CHART_Y + CHART_HEIGHT + shiftY,
                                     ITEM_WIDTH - CHART_WIDTH - CHART_X,
                                     ITEM_HEIGHT - CHART_HEIGHT - CHART_Y),
                              Qt::AlignLeft | Qt::AlignTop,
                              QObject::tr("Time"));
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
        }
    }
    if (this->_time.size() == this->_P.size() && this->_time.size() > 0)
    {
        if (this->_detailIndex > 0 && this->_detailIndex < this->_displayTime)
        {
            painter->setPen(Qt::darkGray);
            shiftY = 0;
            if (this->isDisplayP())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxP.getValue(0) - this->_P[this->_detailIndex].getValue(0)) / (this->_maxP.getValue(0) - this->_minP.getValue(0)) + shiftY;
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT + shiftY), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_P[this->_detailIndex].toString(0)));
                shiftY += ITEM_HEIGHT + ITEM_SPACING;
            }
            if (this->isDisplayQ())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxQ.getValue(0) - this->_Q[this->_detailIndex].getValue(0)) / (this->_maxQ.getValue(0) - this->_minQ.getValue(0)) + shiftY;
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT + shiftY), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_Q[this->_detailIndex].toString(0)));
                shiftY += ITEM_HEIGHT + ITEM_SPACING;
            }
            if (this->isDisplayLambda())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxLambda.getValue(0) - this->_lambda[this->_detailIndex].getValue(0)) / (this->_maxLambda.getValue(0) - this->_minLambda.getValue(0)) + shiftY;
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT + shiftY), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_lambda[this->_detailIndex].toString(0)));
                shiftY += ITEM_HEIGHT + ITEM_SPACING;
            }
            if (this->isDisplayMu())
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(this->_detailIndex) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxMu.getValue(0) - this->_mu[this->_detailIndex].getValue(0)) / (this->_maxMu.getValue(0) - this->_minMu.getValue(0)) + shiftY;
                painter->drawLine(QPointF(CHART_X, y), QPointF(x, y));
                painter->drawLine(QPointF(x, CHART_Y + CHART_HEIGHT + shiftY), QPointF(x, y));
                painter->drawText(QRectF(x + TEXT_MARGIN, y - 300 - TEXT_MARGIN,
                                         300, 300),
                                  Qt::AlignLeft | Qt::AlignBottom,
                                  QString("(%1, %2)").arg(this->_time[this->_detailIndex]).arg(this->_mu[this->_detailIndex].toString(0)));
                shiftY += ITEM_HEIGHT + ITEM_SPACING;
            }
        }
        shiftY = 0;
        if (this->isDisplayP())
        {
            painter->setPen(Qt::darkGreen);
            painter->setBrush(Qt::darkGreen);
            QPen pen = painter->pen();
            pen.setWidth(LINE_WIDTH);
            painter->setPen(pen);
            float lastX = 0.0f;
            float lastY = 0.0f;
            for (int i = 1; i < this->_displayTime; ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxP.getValue(0) - this->_P[i].getValue(0)) / (this->_maxP.getValue(0) - this->_minP.getValue(0)) + shiftY;
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
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
            for (int i = 1; i < this->_displayTime; ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxQ.getValue(0) - this->_Q[i].getValue(0)) / (this->_maxQ .getValue(0)- this->_minQ.getValue(0)) + shiftY;
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
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
            for (int i = 1; i < this->_displayTime; ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxLambda.getValue(0) - this->_lambda[i].getValue(0)) / (this->_maxLambda.getValue(0) - this->_minLambda.getValue(0)) + shiftY;
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
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
            for (int i = 1; i < this->_displayTime; ++i)
            {
                float x = CHART_X + CHART_WIDTH * this->_time.at(i) / this->_time.at(this->_displayTime - 1);
                float y = CHART_Y + CHART_HEIGHT * (this->_maxMu.getValue(0) - this->_mu[i].getValue(0)) / (this->_maxMu.getValue(0) - this->_minMu.getValue(0)) + shiftY;
                if (i > 1)
                {
                    painter->drawLine(QPointF(lastX, lastY), QPointF(x, y));
                }
                lastX = x;
                lastY = y;
            }
            pen.setWidth(1);
            painter->setPen(pen);
            shiftY += ITEM_HEIGHT + ITEM_SPACING;
        }
    }
}

GoMarkovChartData *ItemGoMarkovChart::chartData() const
{
    return this->_chart;
}

void ItemGoMarkovChart::setChart(GoMarkovChartData *chart)
{
    this->_chart = chart;
}

bool ItemGoMarkovChart::isDisplayP() const
{
    return this->_isDisplayP;
}

bool ItemGoMarkovChart::isDisplayQ() const
{
    return this->_isDisplayQ;
}

bool ItemGoMarkovChart::isDisplayLambda() const
{
    return this->_isDisplayLambda;
}

bool ItemGoMarkovChart::isDisplayMu() const
{
    return this->_isDisplayMu;
}

void ItemGoMarkovChart::setIsDisplayP(const bool value)
{
    this->_isDisplayP = value;
}

void ItemGoMarkovChart::setIsDisplayQ(const bool value)
{
    this->_isDisplayQ = value;
}

void ItemGoMarkovChart::setIsDisplayLambda(const bool value)
{
    this->_isDisplayLambda = value;
}

void ItemGoMarkovChart::setIsDisplayMu(const bool value)
{
    this->_isDisplayMu = value;
}

int ItemGoMarkovChart::chartNum() const
{
    int res = 0;
    res += this->isDisplayP();
    res += this->isDisplayQ();
    res += this->isDisplayLambda();
    res += this->isDisplayMu();
    return res;
}

int ItemGoMarkovChart::totalHeight() const
{
    int height = this->chartNum();
    height = height * ITEM_HEIGHT + (height - 1) * ITEM_SPACING + 100;
    return height;
}

int ItemGoMarkovChart::displayIndex() const
{
    return this->_displayIndex;
}

void ItemGoMarkovChart::setDisplayItem(int index, int vectorIndex)
{
    this->_displayIndex = index;
    this->_displayVectorIndex = vectorIndex;
    this->setTitle(this->chartData()->names[index]);
    this->setP(this->chartData()->probabilities[index]);
    this->setQ(this->chartData()->probabilities[index]);
    this->setLambda(this->chartData()->lambdas[index]);
    this->setMu(this->chartData()->mus[index]);
}

void ItemGoMarkovChart::setDisplayItem(const QString name, int vectorIndex)
{
    for (int i = 0; i < this->chartData()->names.size(); ++i)
    {
        if (this->chartData()->names[i] == name)
        {
            this->setDisplayItem(i, vectorIndex);
            break;
        }
    }
}

int ItemGoMarkovChart::displayVectorIndex() const
{
    return this->_displayVectorIndex;
}

void ItemGoMarkovChart::setDisplayVectorIndex(const int index)
{
    this->setDisplayItem(this->_displayIndex, index);
}
