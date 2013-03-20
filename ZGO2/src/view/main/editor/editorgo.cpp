#include "editorgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorGO::EditorGO(QWidget *parent) : EditorAbstract(parent)
{
    // 初始化GO视图。
    this->view = new ViewGO(this);
    // 配置基本的布局。
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("GO Files(*.go)");

    this->_savedID = 1;
}

/**
 * Bind message.
 * @param controller The message controller.
 */
void EditorGO::bindMessage(MessageController *controller)
{
    this->EditorAbstract::bindMessage(controller);
    this->view->bindMessage(controller);
}

void EditorGO::activity()
{
    GOOperatorFactory::setID(this->_savedID);
}

void EditorGO::inactivity()
{
    this->_savedID = GOOperatorFactory::currentID();
}
