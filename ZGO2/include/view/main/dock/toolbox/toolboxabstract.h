#ifndef TOOLBOXABSTRACT_H
#define TOOLBOXABSTRACT_H
/**
 * 抽象的工具栏类型。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include "typeditem.h"
#include "messager.h"

class ToolboxAbstract : public QWidget, public TypedItem, public Messager
{
    Q_OBJECT
public:
    explicit ToolboxAbstract(QWidget *parent = 0);
};

#endif // TOOLBOXABSTRACT_H
