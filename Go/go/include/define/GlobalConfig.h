#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include "stable.h"

class GlobalConfig
{
public:
    static GlobalConfig* getInstance();
    ~GlobalConfig();
    QString lastestPath() const;
    void setLastestPath(const QString path);
    QVector<QString>* lastestFile() const;
    void addLastestFile(const QString file);
    bool isShowDockTool() const;
    bool isShowDockParameter() const;
    bool isShowDockMessage() const;
    void setIsShowDockTool(const bool value);
    void setIsShowDockParameter(const bool value);
    void setIsShowDockMessage(const bool value);
    bool save();
    bool tryOpen();

private:
    GlobalConfig();
    static GlobalConfig *_instance;
    QString _lastestPath;
    QVector<QString> *_lastestFile;
    bool _isShowDockTool;
    bool _isShowDockParameter;
    bool _isShowDockMessage;
};

#endif // GLOBALCONFIG_H
