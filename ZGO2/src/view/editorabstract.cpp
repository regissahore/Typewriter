#include "view/editorabstract.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorAbstract::EditorAbstract(QWidget *parent) : QWidget(parent)
{
    this->_name = tr("Empty");
    this->_path = "";
    this->_modified = true;
    this->_filter = tr("ZHG Files(*.zhg)");
}

/**
 * 获取当前编辑器的ID。
 * @return ID。
 */
qint32 EditorAbstract::id() const
{
    return this->_id;
}

/**
 * 设置当前编辑器的ID。
 * @param id ID。
 */
void EditorAbstract::setId(qint32 id)
{
    this->_id = id;
}

/**
 * 返回当前编辑器的名称。
 * @return 名称。
 */
QString EditorAbstract::name() const
{
    return this->_name;
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
 * 设置当前编辑器的名称。
 * @param name 名称。
 */
void EditorAbstract::setName(QString name)
{
    this->_name = name;
}

/**
 * 设置当前编辑器对应文件的地址，设置之后会触发保存操作。
 * @param path 文件地址。
 */
void EditorAbstract::setPath(QString path)
{
    this->_path = path;
    this->save();
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
        this->setPath(QFileDialog::getSaveFileName(this, tr("Save File"), ".", this->_filter));
        if (this->path() == "")
        {
            return false; // 选取文件操作被取消。
        }
        QFile file(this->path());
        this->setName(file.fileName());
    }
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
