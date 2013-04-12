#ifndef TOOLBOXNULL_H
#define TOOLBOXNULL_H
/**
 * 无内容的工具栏。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QLabel>
#include <QGridLayout>
#include "toolboxabstract.h"

class ToolboxNull : public ToolboxAbstract
{
    Q_OBJECT
public:
    explicit ToolboxNull(QWidget *parent = 0);
};

#endif // TOOLBOXNULL_H
