#ifndef IDENTIFIEDNAMEDITEM_H
#define IDENTIFIEDNAMEDITEM_H
#include "stable.h"

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
