#ifndef GOSIGNALFACTORY_H
#define GOSIGNALFACTORY_H
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
