#ifndef FACTORYABSTRACT_H
#define FACTORYABSTRACT_H

class FactoryAbstract
{
public:
    FactoryAbstract();
    void setId(int id);
    /**
     * 生成对象。
     * @param type 对象的类别。
     * @return 生成的对象。
     */
    virtual void* produce(int type) = 0;

protected:
    int id();

private:
    int _id; /** 用于自动增长的ID。 */
};

#endif // FACTORYABSTRACT_H
