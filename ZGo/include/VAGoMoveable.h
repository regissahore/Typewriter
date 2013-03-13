#ifndef VAGOMOVEABLE_H
#define VAGOMOVEABLE_H
/**
 * 可以移动的可绘制单元。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "VAGoDrawable.h"

class VAGoMoveable : public VAGoDrawable
{
public:
    VAGoMoveable();
    bool isMoving(void) const;
    void setMoving(bool value);

protected:
    bool _moving; /** 当前是否处于移动状态。 */
};

#endif // VAGOMOVEABLE_H
