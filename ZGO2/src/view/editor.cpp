#include "view/editor.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
Editor::Editor(QWidget *parent) :
    QWidget(parent)
{
    this->tabWidget = new QTabWidget(this);
    this->tabWidget->setMovable(true);
    this->tabWidget->setTabsClosable(true);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->tabWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->factory = new EditorFactory();
    EditorAbstract *editor = (EditorAbstract*)this->factory->produce(EditorFactory::TYPE_WELCOME);
    this->tabWidget->addTab(editor, editor->name());
}
