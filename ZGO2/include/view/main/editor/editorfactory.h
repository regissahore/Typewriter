#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
/**
 * 用于生成相应的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
class EditorAbstract;

class EditorFactory
{
public:
    enum EditorType
    {
        EDITOR_TYPE_NULL,       /** 没有选择编辑器。 */
        EDITOR_TYPE_WELCOME,    /** 欢迎屏幕。 */
        EDITOR_TYPE_GO,         /** GO图编辑器。 */
        EDITOR_TYPE_GO_MARKOV,  /** Markov Repairable system. */
        EDITOR_TYPE_WEBVIEW
    };
    static EditorAbstract* produce(int type);
};

#endif // EDITORFACTORY_H
