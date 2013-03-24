#ifndef EDITOR_H
#define EDITOR_H
/**
 * 编辑器的总体，提供编辑器的管理。
 * 注意：编辑器应该最后加载。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "messager.h"
#include "editorfactory.h"

class Editor : public QWidget, public Messager
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    bool trySaveAll();
    bool tryCloseAll();
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    QTabWidget *_tabWidget; /** 用于维护多个编辑器。 */
    EditorFactory *_factory; /** 用于实例化编辑器的工厂类。 */
    QVector<EditorAbstract*> *_editors; /** 编辑器的集合。 */
    void createNewTab();
    void tryOpen();

protected slots:
    bool tryCloseTab(int index);
    void currentChange(int index);
};

#endif // EDITOR_H
