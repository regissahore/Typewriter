#ifndef TOOLBOXABSTRACT_H
#define TOOLBOXABSTRACT_H
#include <QWidget>
#include "TypedItem.h"
#include "Messager.h"

class QPushButton;

class ToolboxAbstract : public QWidget, public TypedItem, public Messager
{
    Q_OBJECT
public:
    explicit ToolboxAbstract(QWidget *parent = 0);
    virtual ~ToolboxAbstract();

protected:
    QPushButton *_selectedTool;
    void setSelectedTool(QPushButton *tool);
};

#endif // TOOLBOXABSTRACT_H
