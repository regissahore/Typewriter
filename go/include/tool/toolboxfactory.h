#ifndef TOOLBOXFACTORY_H
#define TOOLBOXFACTORY_H
class ToolboxAbstract;

class ToolboxFactory
{
public:
    enum ToolboxType
    {
        TOOLBOX_TYPE_NULL,
        TOOLBOX_TYPE_Go,
        TOOLBOX_TYPE_Go_MARKOV
    };
    static ToolboxAbstract* produce(const int type);
};

#endif // TOOLBOXFACTORY_H
