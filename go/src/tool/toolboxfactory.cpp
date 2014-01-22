#include "ToolboxFactory.h"
#include "ToolboxAbstract.h"
#include "ToolboxNull.h"
#include "ToolboxGo.h"
#include "ToolboxGoMarkov.h"

ToolboxAbstract* ToolboxFactory::produce(const int type)
{
    ToolboxAbstract *toolbox = 0L;
    switch (type)
    {
    case TOOLBOX_TYPE_NULL:
        toolbox = new ToolboxNull();
        break;
    case TOOLBOX_TYPE_Go:
        toolbox = new ToolboxGo();
        break;
    case TOOLBOX_TYPE_Go_MARKOV:
        toolbox = new ToolboxGoMarkov();
        break;
    default:
        break;
    }
    if (toolbox != 0L)
    {
        toolbox->setType(type);
    }
    return toolbox;
}
