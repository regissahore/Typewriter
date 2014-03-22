#ifndef TOOLBOXNULL_H
#define TOOLBOXNULL_H
#include "stable.h"
#include "ToolboxAbstract.h"

class ToolboxNull : public ToolboxAbstract
{
    Q_OBJECT
public:
    explicit ToolboxNull(QWidget *parent = 0);
};

#endif // TOOLBOXNULL_H
