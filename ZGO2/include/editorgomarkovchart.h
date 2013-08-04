#ifndef EDITORGOMARKOVCHART_H
#define EDITORGOMARKOVCHART_H
/**
 * The editor to show the chart result of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "editorabstract.h"

class ViewGOMarkovChart;

class EditorGOMarkovChart : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGOMarkovChart(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void activate();
    bool save();
    bool tryOpen(const QString path);

protected:
    ViewGOMarkovChart *_view;
};

#endif // EDITORGOMARKOVCHART_H
