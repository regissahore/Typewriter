#ifndef TOOLBOXFACTORY_H
#define TOOLBOXFACTORY_H
/**
 * 工具栏工厂类。
 * @author ZHG <CyberZHG@gmaill.com>
 */
class ToolboxAbstract;

class ToolboxFactory
{
public:
    enum ToolboxType
    {
        TOOLBOX_TYPE_NULL,
        TOOLBOX_TYPE_GO,
        TOOLBOX_TYPE_GO_MARKOV
    };
    static ToolboxAbstract* produce(const int type);
};

#endif // TOOLBOXFACTORY_H
