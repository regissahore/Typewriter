#ifndef EDITORGO_H
#define EDITORGO_H
#include <QLabel>
#include <QWidget>
#include <QSplitter>
#include <QGridLayout>
#include <QGraphicsView>
#include "editorabstract.h"
#include "viewgo.h"
#include "gooperatorfactory.h"

class EditorGO : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGO(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    bool save();
    bool tryOpen(const QString path);
    void activate();
    
protected:
    ViewGO *_view;
};

#endif // EDITORGO_H
