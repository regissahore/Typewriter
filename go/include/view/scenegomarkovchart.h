#ifndef SCENEGOMARKOVCHART_H
#define SCENEGOMARKOVCHART_H
#include <QGraphicsScene>

class ItemArrow;
class GoMarkovChartData;
class ItemGoMarkovChart;
class MessageController;

class SceneGoMarkovChart : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGoMarkovChart(QObject *parent = 0);
    ~SceneGoMarkovChart();
    void activate(MessageController *controller);
    bool save(QString path);
    bool tryOpen(QString path);
    void selectOperator(int index);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
    GoMarkovChartData *_chartData;
    ItemGoMarkovChart *_chartItem;
    int _currentIndex;
};

#endif // SCENEGOMARKOVCHART_H
