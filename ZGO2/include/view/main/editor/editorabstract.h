#ifndef EDITORABSTRACT_H
#define EDITORABSTRACT_H
/**
 * 编辑器的抽象实现。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "typeditem.h"
#include "messager.h"
#include "nameditem.h"

class EditorAbstract : public QWidget, public IdentifiedItem, public NamedItem, public TypedItem, public Messager
{
    Q_OBJECT
public:
    explicit EditorAbstract(QWidget *parent = 0);
    virtual ~EditorAbstract();
    QString path() const;
    void setPath(QString path);
    bool modified() const;
    virtual bool trySave();
    virtual bool tryClose();
    int tool() const;
    void setTool(const int type);
    void bindMessage(MessageController *controller);
    virtual void activate();
    virtual void inactivate();

protected:
    QString _filter; /** 用于文件保存的类型。 */
    virtual bool save();
    void setModified(bool value);

private:
    QString _path; /** 正在编辑的文件的路径，如果没保存则为空。*/
    bool _modified; /** 是否被编辑过。 */
    int _tool;

signals:
    /**
     * 被编辑的状态发生改变。
     * @param id 当前的ID。
     */
    void modifyChanged(qint32 id);
};

#endif // EDITORABSTRACT_H
