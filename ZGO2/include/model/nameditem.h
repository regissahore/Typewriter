#ifndef IDENTIFIEDNAMEDITEM_H
#define IDENTIFIEDNAMEDITEM_H
/**
 * 有名称描述和ID的数据。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QString>

class NamedItem
{
public:
    NamedItem();
    const QString name() const;
    void setName(const QString name);

private:
    QString _name;
};

#endif // IDENTIFIEDNAMEDITEM_H
