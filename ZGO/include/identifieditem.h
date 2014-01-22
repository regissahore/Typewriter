#ifndef IDENTIFIEDITEM_H
#define IDENTIFIEDITEM_H

class IdentifiedItem
{
public:
    IdentifiedItem();
    int id() const;
    virtual void setId(const int id);

private:
    int _id; /** 标识数值。 */
};

#endif // IDENTIFIEDITEM_H
