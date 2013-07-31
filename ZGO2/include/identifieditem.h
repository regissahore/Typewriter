#ifndef IDENTIFIEDITEM_H
#define IDENTIFIEDITEM_H
/**
 * 有唯一ID标识的数据。
 * @author ZHG <CyberZHG@gmail.com>
 */

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
