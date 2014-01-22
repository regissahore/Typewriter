#ifndef VIEWGOMARKOVCHART_H
#define VIEWGOMARKOVCHART_H
#include "GraphicsView.h"

class SceneGoMarkovChart;
class MessageController;

class ViewGoMarkovChart : public GraphicsView
{
    Q_OBJECT
public:
    explicit ViewGoMarkovChart(QWidget *parent);
    void activate(MessageController *controller);
    bool save(QString path);
    bool tryOpen(QString path);

protected:
    SceneGoMarkovChart *_scene;
};

#endif // VIEWGOMARKOVCHART_H
