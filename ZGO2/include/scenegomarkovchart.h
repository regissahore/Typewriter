#ifndef SCENEGOMARKOVCHART_H
#define SCENEGOMARKOVCHART_H
/**
 * The scene to show the result chart of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsScene>

class ItemArrow;
class GOMarkovChartData;
class ItemGOMarkovChart;
class MessageController;

class SceneGOMarkovChart : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGOMarkovChart(QObject *parent = 0);
    ~SceneGOMarkovChart();
    void activate(MessageController *controller);
    bool save(QString path);
    bool tryOpen(QString path);
    void selectOperator(int index);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
    GOMarkovChartData *_chartData;
    ItemGOMarkovChart *_chartItem;
    int _currentIndex;
};

#endif // SCENEGOMARKOVCHART_H
