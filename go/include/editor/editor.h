#ifndef EDITOR_H
#define EDITOR_H
#include <memory>
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
    void messageEvent(std::shared_ptr<Message> message);

protected:
    QTabWidget *_tabWidget;
    EditorFactory *_factory;
    QVector<EditorAbstract*> *_editors;
    void createNewTab(int type);
    void tryOpen();
    void openExist(QString filePath);

protected slots:
    bool tryCloseTab(int index);
    void currentChange(int index);
};

#endif // EDITOR_H
