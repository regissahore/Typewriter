#ifndef DEFINATIONEDITORTYPE_H
#define DEFINATIONEDITORTYPE_H
/**
 * 对编辑器类型的定义。
 * @author ZHG <CyberZHG@gmail.com>
 */

class DefinationEditorType
{
public:
    enum EditorType
    {
        EDITOR_TYPE_NULL,       /** 没有选择编辑器。 */
        EDITOR_TYPE_WELCOME,    /** 欢迎屏幕。 */
        EDITOR_TYPE_GO,         /** GO图编辑器。 */
        EDITOR_TYPE_WEBVIEW
    };
};

#endif // DEFINATIONEDITORTYPE_H
