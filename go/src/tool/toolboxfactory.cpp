#include "ToolboxFactory.h"
#include "ToolboxAbstract.h"
#include "ToolboxNull.h"
#include "ToolboxGo.h"
#include "ToolboxGoMarkov.h"

ToolboxAbstract* ToolboxFactory::produce(const int type)
{
    ToolboxAbstract *toolbox = nullptr;
    switch (type)
    {
    case TOOLBOX_TYPE_NULL:
        toolbox = new ToolboxNull();
        break;
    case TOOLBOX_TYPE_GO:
        toolbox = new ToolboxGo();
        break;
    case TOOLBOX_TYPE_GO_MARKOV:
        toolbox = new ToolboxGoMarkov();
        break;
    default:
        break;
    }
    if (toolbox != nullptr)
    {
        toolbox->setType(type);
    }
    return toolbox;
}
