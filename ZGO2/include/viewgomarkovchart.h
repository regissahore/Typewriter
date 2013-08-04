#ifndef VIEWGOMARKOVCHART_H
#define VIEWGOMARKOVCHART_H
/**
 * The view to show the result chart of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "graphicsview.h"

class SceneGOMarkovChart;
class MessageController;

class ViewGOMarkovChart : public GraphicsView
{
    Q_OBJECT
public:
    explicit ViewGOMarkovChart(QWidget *parent);
    void activate(MessageController *controller);
    bool save(QString path);
    bool tryOpen(QString path);

protected:
    SceneGOMarkovChart *_scene;
};

#endif // VIEWGOMARKOVCHART_H
