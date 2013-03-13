#ifndef MCGOAUTOINCREMENTALFACTORY_H
#define MCGOAUTOINCREMENTALFACTORY_H
/**
 * 拥有自动增长ID的工厂类。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class MCGoAutoIncrementalFactory
{
public:
    MCGoAutoIncrementalFactory();
    void setStartID(qint32 id);

protected:
    qint32 _id;
    qint32 id(void);
};

#endif // MCGOAUTOINCREMENTALFACTORY_H
