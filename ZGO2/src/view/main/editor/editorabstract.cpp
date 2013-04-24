#include <QFile>
#include "editorabstract.h"
#include "messagefactory.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorAbstract::EditorAbstract(QWidget *parent) : QWidget(parent)
{
    this->setName(tr("Empty"));
    this->setPath("");
    this->_modified = true;
    this->_filter = tr("ZHG Files(*.zhg)");
    this->_suffix = "zhg";
}

EditorAbstract::~EditorAbstract()
{
    this->MessageListener::~MessageListener();
}

/**
 * 返回当前编辑器对应文件的地址。
 * @return 文件地址。
 */
QString EditorAbstract::path() const
{
    return this->_path;
}

/**
 * 设置当前编辑器对应文件的地址。
 * @param path 文件地址。
 */
void EditorAbstract::setPath(QString path)
{
    this->_path = path;
    if (path != "")
    {
        QString name = "";
        for (int i = path.length() - 1; i >= 0; --i)
        {
            if (path.at(i) == '/' || path.at(i) == '\\')
            {
                break;
            }
            name = path.at(i) + name;
        }
        this->setName(name);
    }
}

/**
 * 当前编辑器的内容是否被修改。
 * @return 如果被修改则返回true，否则返回false。
 */
bool EditorAbstract::modified() const
{
    return this->_modified;
}

/**
 * 尝试保存文件，如果没设置文件地址将弹出对话框询问位置。
 * @return 如果文件保存成功返回true，否则返回false。
 */
bool EditorAbstract::trySave()
{
    if (this->path() == "")
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), ".", this->_filter);
        if (filePath == "")
        {
            return false;
        }
        if (QFileInfo(filePath).suffix() != this->_suffix)
        {
            filePath.append("." + this->_suffix);
        }
        this->setPath(filePath);
    }
    if (this->save())
    {
        this->setModified(false);
        return true;
    }
    return false;
}

/**
 * Try save file to another path.
 * @return Returns true is succeed, otherwise false.
 */
bool EditorAbstract::trySaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File As"), ".", this->_filter);
    if (filePath == "")
    {
        return false;
    }
    if (QFileInfo(filePath).suffix() != this->_suffix)
    {
        filePath.append("." + this->_suffix);
    }
    this->setPath(filePath);
    if (this->save())
    {
        this->setModified(false);
        return true;
    }
    return false;
}

/**
 * 尝试关闭编辑器。
 * @return 如果编辑器允许则返回true，否则返回false。
 */
bool EditorAbstract::tryClose()
{
    if (this->modified())
    {
        QMessageBox::StandardButton result = QMessageBox::warning(this, tr("Warning"), tr("The file is modified, do you want to save the file?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        if (result == QMessageBox::Yes)
        {
            return this->trySave(); // 如果正常保存文件则可以正常关闭。
        }
        if (result == QMessageBox::No)
        {
            return true; // 不保存文件直接关闭。
        }
        return false; // 操作取消。
    }
    return true; // 没有修改，可以直接关闭。
}

/**
 * Try open a file.
 * @param path The file path.
 */
bool EditorAbstract::tryOpen(const QString path)
{
    Q_UNUSED(path);
    return false;
}

/**
 * 保存编辑器的内容。
 * @return 如果保存成功返回true，否则返回false。
 */
bool EditorAbstract::save()
{
    return true;
}

/**
 * 设置是否修改的状态，如果状态发生改变则会发出信号。
 * @param value 是否被修改。
 */
void EditorAbstract::setModified(bool value)
{
    if (this->modified() != value)
    {
        emit modifyChanged(this->id());
    }
    this->_modified = value;
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void EditorAbstract::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

/**
 * The function called when the editor is activate.
 */
void EditorAbstract::activate()
{
}

/**
 * The function called when the editor is inactivate.
 */
void EditorAbstract::inactivate()
{
}
