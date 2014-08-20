#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
class EditorAbstract;

class EditorFactory
{
public:
    enum EditorType
    {
        EDITOR_TYPE_NULL,
        EDITOR_TYPE_WELCOME,
        EDITOR_TYPE_GO,
        EDITOR_TYPE_GO_MARKOV,
        EDITOR_TYPE_WEBVIEW
    };
    static EditorAbstract* produce(int type);
};

#endif // EDITORFACTORY_H
