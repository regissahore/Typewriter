#include "toolboxfactory.h"
#include "toolboxabstract.h"
#include "toolboxnull.h"
#include "toolboxgo.h"
#include "toolboxgomarkov.h"

/**
 * 生成对应的工具栏。
 * @param type 工具栏类型。
 * @return 工具栏。
 */
ToolboxAbstract* ToolboxFactory::produce(const int type)
{
    ToolboxAbstract *toolbox = 0L;
    switch (type)
    {
    case TOOLBOX_TYPE_NULL:
        toolbox = new ToolboxNull();
        break;
    case TOOLBOX_TYPE_GO:
        toolbox = new ToolboxGO();
        break;
    case TOOLBOX_TYPE_GO_MARKOV:
        toolbox = new ToolboxGOMarkov();
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
