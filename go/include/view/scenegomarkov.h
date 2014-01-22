#ifndef SCENEGOMARKOV_H
#define SCENEGOMARKOV_H
#include "SceneGo.h"

class ItemGoMarkovEquivalent;

class SceneGoMarkov : public SceneGo
{
    Q_OBJECT
public:
    SceneGoMarkov(QObject *parent = 0);
    GoGraph* generatorGoGraph();
    QList<ItemGoMarkovEquivalent *> getTopologyOrder(QList<ItemGoMarkovEquivalent *> equivalents);
    void analysisProbability(const QString filePath);
    void analysisCut(const QString filePath);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    double _analysisTotalTime;
    double _analysisCount;
    int _analysisCutOrder;
};

#endif // SCENEGOMARKOV_H
