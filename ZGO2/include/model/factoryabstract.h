#ifndef FACTORYABSTRACT_H
#define FACTORYABSTRACT_H
/**
 * 一个有自动增长分配ID的工厂类。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class FactoryAbstract
{
public:
    FactoryAbstract();
    void setId(qint32 id);
    /**
     * 生成对象。
     * @param type 对象的类别。
     * @return 生成的对象。
     */
    virtual void* produce(qint32 type) = 0;

protected:
    qint32 id();

private:
    qint32 _id; /** 用于自动增长的ID。 */
};

#endif // FACTORYABSTRACT_H
