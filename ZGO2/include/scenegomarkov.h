#ifndef SCENEGOMARKOV_H
#define SCENEGOMARKOV_H
/**
 * The graphics scene for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "scenego.h"

class ItemGOMarkovEquivalent;

class SceneGOMarkov : public SceneGO
{
    Q_OBJECT
public:
    SceneGOMarkov(QObject *parent = 0);
    GOGraph* generatorGOGraph();
    QList<ItemGOMarkovEquivalent *> getTopologyOrder(QList<ItemGOMarkovEquivalent *> equivalents);
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
