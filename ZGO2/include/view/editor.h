#ifndef EDITOR_H
#define EDITOR_H
/**
 * 编辑器的总体，提供编辑器的管理。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "view/editorfactory.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    bool trySaveAll();
    bool tryCloseAll();

protected:
    QTabWidget *tabWidget; /** 用于维护多个编辑器。 */
    EditorFactory *factory; /** 用于实例化编辑器的工厂类。 */
    QVector<EditorAbstract*> *editors; /** 编辑器的集合。 */

protected slots:
    bool tryCloseTab(int index);
};

#endif // EDITOR_H
