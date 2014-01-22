#ifndef TYPEDITEM_H
#define TYPEDITEM_H

class TypedItem
{
public:
    TypedItem();
    int type() const;
    virtual void setType(const int type);

private:
    int _type; /** 操作符的类型。 */
};

#endif // TYPEDITEM_H
