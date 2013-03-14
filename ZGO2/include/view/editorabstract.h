#ifndef EDITORABSTRACT_H
#define EDITORABSTRACT_H
/**
 * 编辑器的抽象实现。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

class EditorAbstract : public QWidget
{
    Q_OBJECT
public:
    explicit EditorAbstract(QWidget *parent = 0);
    qint32 id() const;
    void setId(qint32 id);
    QString name() const;
    QString path() const;
    void setName(QString name);
    void setPath(QString path);
    bool modified() const;
    bool trySave();
    bool tryClose();

protected:
    QString _filter; /** 用于文件保存的类型。 */
    bool save();
    void setModified(bool value);

private:
    QString _name; /** 编辑器的名称。 */
    QString _path; /** 正在编辑的文件的路径，如果没保存则为空。*/
    bool _modified; /** 是否被编辑过。 */
    qint32 _id; /** 用于区别的ID。 */

signals:
    /**
     * 被编辑的状态发生改变。
     * @param id 当前的ID。
     */
    void modifyChanged(qint32 id);
};

#endif // EDITORABSTRACT_H
