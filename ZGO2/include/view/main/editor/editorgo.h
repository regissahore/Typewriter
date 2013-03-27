#ifndef EDITORGO_H
#define EDITORGO_H
/**
 * 基本的GO法编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
    void messageEvent(Message *message);
    void activate();
    void inactivate();
    bool save();
    bool tryOpen(const QString path);
    
protected:
    ViewGO *view;
    int _savedOperatorID;
    int _savedSignalID;
};

#endif // EDITORGO_H
