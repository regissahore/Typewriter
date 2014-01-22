#ifndef EDITOR_H
#define EDITOR_H
#include <QVector>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "Messager.h"
#include "EditorFactory.h"

class EditorAbstract;

class Editor : public QWidget, public Messager
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    bool trySaveAll();
    bool tryCloseAll();
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);

protected:
    QTabWidget *_tabWidget; /** 用于维护多个编辑器。 */
    EditorFactory *_factory; /** 用于实例化编辑器的工厂类。 */
    QVector<EditorAbstract*> *_editors; /** 编辑器的集合。 */
    void createNewTab(int type);
    void tryOpen();
    void openExist(QString filePath);

protected slots:
    bool tryCloseTab(int index);
    void currentChange(int index);
};

#endif // EDITOR_H
