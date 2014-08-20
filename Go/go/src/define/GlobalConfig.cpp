#include <QFile>
#include <QDomDocument>
#include "GlobalConfig.h"

GlobalConfig* GlobalConfig::_instance = 0;

GlobalConfig::GlobalConfig()
{
    this->setLastestPath(".");
    this->_lastestFile = new QVector<QString>();
    this->setIsShowDockTool(true);
    this->setIsShowDockParameter(true);
    this->setIsShowDockMessage(true);
    this->tryOpen();
}

GlobalConfig::~GlobalConfig()
{
    this->_lastestFile->clear();
    delete this->_lastestFile;
}

GlobalConfig* GlobalConfig::getInstance()
{
    if (0 == _instance)
    {
        _instance = new GlobalConfig();
    }
    return _instance;
}

QString GlobalConfig::lastestPath() const
{
    return this->_lastestPath;
}

void GlobalConfig::setLastestPath(const QString path)
{
    this->_lastestPath = path;
}

QVector<QString>* GlobalConfig::lastestFile() const
{
    return this->_lastestFile;
}

void GlobalConfig::addLastestFile(const QString file)
{
    for (int i = 0; i < this->lastestFile()->size(); ++i)
    {
        if (this->lastestFile()->at(i) == file)
        {
            return;
        }
    }
    if (this->lastestFile()->size() >= 10)
    {
        this->lastestFile()->pop_back();
    }
    this->lastestFile()->push_front(file);
}

bool GlobalConfig::isShowDockTool() const
{
    return this->_isShowDockTool;
}

bool GlobalConfig::isShowDockParameter() const
{
    return this->_isShowDockParameter;
}

bool GlobalConfig::isShowDockMessage() const
{
    return this->_isShowDockMessage;
}

void GlobalConfig::setIsShowDockTool(const bool value)
{
    this->_isShowDockTool = value;
}

void GlobalConfig::setIsShowDockParameter(const bool value)
{
    this->_isShowDockParameter = value;
}

void GlobalConfig::setIsShowDockMessage(const bool value)
{
    this->_isShowDockMessage = value;
}

bool GlobalConfig::save()
{
    QDomDocument document;
    QDomElement root = document.createElement("Global_Config");
    root.setAttribute("support", "ZHG");
    root.setAttribute("dock_tool", this->isShowDockTool());
    root.setAttribute("dock_parameter", this->isShowDockParameter());
    root.setAttribute("dock_message", this->isShowDockMessage());
    root.setAttribute("lastest_path", this->lastestPath());
    document.appendChild(root);
    QDomElement pathElement = document.createElement("Lastest_File");
    for (int i = 0; i < this->lastestFile()->size(); ++i)
    {
        QDomElement pathNode = document.createElement("Path");
        pathNode.setAttribute("path", this->lastestFile()->at(i));
        pathElement.appendChild(pathNode);
    }
    root.appendChild(pathElement);
    QFile file("global.config");
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    file.write(document.toByteArray(4));
    file.flush();
    file.close();
    return true;
}

bool GlobalConfig::tryOpen()
{
    QDomDocument document;
    QFile file("global.config");
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    QDomElement root = document.firstChildElement();
    this->setIsShowDockTool(root.attribute("dock_tool", "1").toInt());
    this->setIsShowDockParameter(root.attribute("dock_parameter", "1").toInt());
    this->setIsShowDockMessage(root.attribute("dock_message", "1").toInt());
    this->setLastestPath(root.attribute("lastest_path", "."));
    QDomElement pathElement = root.firstChildElement();
    for (auto pathNode = pathElement.firstChildElement(); !pathNode.isNull(); pathNode = pathNode.nextSiblingElement())
    {
        this->lastestFile()->push_back(pathNode.attribute("path"));
    }
    return true;
}
