#include "toolboxfactory.h"

/**
 * 构造函数。
 */
ToolboxFactory::ToolboxFactory()
{
}

/**
 * 生成对应的工具栏。
 * @param type 工具栏类型。
 * @return 工具栏。
 */
void* ToolboxFactory::produce(int type)
{
    ToolboxAbstract *toolbox = 0L;
    switch (type)
    {
    case DefinationToolboxType::TOOLBOX_TYPE_NULL:
        toolbox = new ToolboxNull();
        break;
    case DefinationToolboxType::TOOLBOX_TYPE_GO:
        toolbox = new ToolboxGO();
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
