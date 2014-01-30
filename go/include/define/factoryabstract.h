#ifndef FACTORYABSTRACT_H
#define FACTORYABSTRACT_H

class FactoryAbstract
{
public:
    FactoryAbstract();
    void setId(int id);
    virtual void* produce(int type) = 0;

protected:
    int id();

private:
    int _id;
};

#endif // FACTORYABSTRACT_H
