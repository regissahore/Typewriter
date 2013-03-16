#ifndef TYPEDITEM_H
#define TYPEDITEM_H
/**
 * 有类型的数据。
 * @author ZHG <CyberZHG@gmail.com>
 */

class TypedItem
{
public:
    TypedItem();
    int type() const;
    void setType(const int type);

private:
    int _type; /** 操作符的类型。 */
};

#endif // TYPEDITEM_H
