#ifndef TOOLBOXGO_H
#define TOOLBOXGO_H
/**
 * GO法的工具栏。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QPushButton>
#include <QGridLayout>
#include "toolboxabstract.h"

class ToolboxGO : public ToolboxAbstract
{
    Q_OBJECT
public:
    explicit ToolboxGO(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // TOOLBOXGO_H
