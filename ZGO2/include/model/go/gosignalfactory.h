#ifndef GOSIGNALFACTORY_H
#define GOSIGNALFACTORY_H
/**
 * A GO Signal model factory.
 * The model produced will bind to a auto increment ID.
 * The start ID value must be set before use it beacause it is a static class.
 * @author ZHG <CyberZHG@gmail.com>
 */
class GOSignal;

class GOSignalFactory
{
public:
    GOSignalFactory();
    static GOSignal* produce();
    static void setID(const int id);
    static int currentID();

private:
    static int _autoID;
};

#endif // GOSIGNALFACTORY_H
