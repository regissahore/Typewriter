#ifndef EDITORGO_H
#define EDITORGO_H
/**
 * 基本的GO法编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QGraphicsView>
#include "view/editorabstract.h"

class EditorGO : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGO(QWidget *parent = 0);
    
protected:
    QGraphicsView *view;
};

#endif // EDITORGO_H
