#ifndef VIEWGOMARKOVCHART_H
#define VIEWGOMARKOVCHART_H
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
