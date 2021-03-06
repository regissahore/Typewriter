#ifndef EDITORGO_H
#define EDITORGO_H
#include "stable.h"
#include "EditorAbstract.h"
#include "ViewGo.h"
#include "GoOperatorFactory.h"
using namespace std;

class EditorGo : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGo(QWidget *parent = 0);
    void messageEvent(QSharedPointer<Message> message);
    bool save();
    bool tryOpen(const QString path);
    void activate();
    
protected:
    ViewGo *_view;
};

#endif // EDITORGO_H
