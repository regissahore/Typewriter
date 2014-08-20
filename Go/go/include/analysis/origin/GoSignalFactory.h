#ifndef GOSIGNALFACTORY_H
#define GOSIGNALFACTORY_H
class GoSignal;

class GoSignalFactory
{
public:
    GoSignalFactory();
    static GoSignal* produce();
    static void setID(const int id);
    static int currentID();

private:
    static int _autoID;
};

#endif // GOSIGNALFACTORY_H
