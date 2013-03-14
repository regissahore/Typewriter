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
#include "view/editorabstract.h"
#include "view/viewgo.h"

class EditorGO : public EditorAbstract
{
    Q_OBJECT
public:
    explicit EditorGO(QWidget *parent = 0);
    
protected:
    ViewGO *view;
};

#endif // EDITORGO_H
