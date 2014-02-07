#ifndef EDITORGOMARKOVCHART_H
#define EDITORGOMARKOVCHART_H
#include "EditorAbstract.h"

class ViewGoMarkovChart;

class EditorGoMarkovChart : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGoMarkovChart(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void activate();
    bool save();
    bool tryOpen(const QString path);

protected:
    ViewGoMarkovChart *_view;
};

#endif // EDITORGOMARKOVCHART_H
