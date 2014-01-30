#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
class EditorAbstract;

class EditorFactory
{
public:
    enum EditorType
    {
        EDITOR_TYPE_NULL,       /** 没有选择编辑器。 */
        EDITOR_TYPE_WELCOME,    /** 欢迎屏幕。 */
        EDITOR_TYPE_GO,         /** Go图编辑器。 */
        EDITOR_TYPE_GO_MARKOV,  /** Markov Repairable system. */
        EDITOR_TYPE_WEBVIEW,
        EDITOR_TYPE_GO_MARKOV_CHART
    };
    static EditorAbstract* produce(int type);
};

#endif // EDITORFACTORY_H
