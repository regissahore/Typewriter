#include <QFile>
#include "EditorAbstract.h"
#include "MessageFactory.h"
#include "GlobalConfig.h"

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
    this->Messager::~Messager();
}

QString EditorAbstract::path() const
{
    return this->_path;
}

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

bool EditorAbstract::modified() const
{
    return this->_modified;
}

bool EditorAbstract::trySave()
{
    if (this->path() == "")
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), GlobalConfig::getInstance()->lastestPath(), this->_filter);
        if (filePath == "")
        {
            return false;
        }
        GlobalConfig::getInstance()->setLastestPath(QFileInfo(filePath).absolutePath());
        GlobalConfig::getInstance()->addLastestFile(QFileInfo(filePath).absoluteFilePath());
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

bool EditorAbstract::trySaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File As"), GlobalConfig::getInstance()->lastestPath(), this->_filter);
    if (filePath == "")
    {
        return false;
    }
    GlobalConfig::getInstance()->setLastestPath(QFileInfo(filePath).absolutePath());
    GlobalConfig::getInstance()->addLastestFile(QFileInfo(filePath).absoluteFilePath());
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

bool EditorAbstract::tryOpen(const QString path)
{
    Q_UNUSED(path);
    return false;
}

bool EditorAbstract::save()
{
    return true;
}

void EditorAbstract::setModified(bool value)
{
    if (this->modified() != value)
    {
        emit modifyChanged(this->id());
    }
    this->_modified = value;
}

void EditorAbstract::activate()
{
}

void EditorAbstract::inactivate()
{
}
