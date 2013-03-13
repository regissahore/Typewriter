#ifndef MAGOITEM_H
#define MAGOITEM_H
/**
 * GO图中的基本单位。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <QObject>

class MAGoItem
{
public:
    qint32 id(void) const;
    void setId(qint32 id);
    qint32 type(void) const;
    void setType(qint32 type);

protected:
    qint32 _id;
    qint32 _type;
};

#endif // MAGOITEM_H
