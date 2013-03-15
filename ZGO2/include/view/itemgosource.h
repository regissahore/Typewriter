#ifndef ITEMGOSOURCE_H
#define ITEMGOSOURCE_H
/**
 * GO操作符中的信号发生器。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "view/itemmoveable.h"

class ItemGOSource
{
public:
    ItemGOSource();
    int type() const;
    void setType(int type);

private:
    int _type;
};

#endif // ITEMGOSOURCE_H
