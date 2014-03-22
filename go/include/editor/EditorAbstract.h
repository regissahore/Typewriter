#ifndef EDITORABSTRACT_H
#define EDITORABSTRACT_H
#include "stable.h"
#include "TypedItem.h"
#include "Messager.h"
#include "NamedItem.h"

class EditorAbstract : public QWidget, public IdentifiedItem, public NamedItem, public TypedItem, public Messager
{
    Q_OBJECT
public:
    explicit EditorAbstract(QWidget *parent = 0);
    virtual ~EditorAbstract();
    QString path() const;
    virtual void setPath(QString path);
    bool modified() const;
    virtual bool trySave();
    virtual bool trySaveAs();
    virtual bool tryClose();
    virtual bool tryOpen(const QString path);
    virtual void activate();
    virtual void inactivate();
    void setModified(bool value);

protected:
    QString _filter;
    QString _suffix;
    virtual bool save();

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
