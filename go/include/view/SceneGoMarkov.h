#ifndef SCENEGOMARKOV_H
#define SCENEGOMARKOV_H
#include <QSharedPointer>
#include "SceneGo.h"

class GoMarkovGraph;
class ItemGoMarkovEquivalent;

class SceneGoMarkov : public SceneGo
{
    Q_OBJECT
public:
    SceneGoMarkov(QObject *parent = 0);
    QSharedPointer<GoMarkovGraph> generateGoMarkovGraph();
    QList<ItemGoMarkovEquivalent *> getTopologyOrder(QList<ItemGoMarkovEquivalent *> equivalents);
    virtual void analysisProbability(const QString filePath) override;
    virtual void analysisCut(const QString filePath) override;
    virtual void analysisPath(const QString filePath) override;
    void save(QDomDocument &document, QDomElement &root) override;
    bool tryOpen(QDomElement &root) override;

protected:
    double _analysisTotalTime;
    double _analysisCount;
    int _analysisCutOrder;
};

#endif // SCENEGOMARKOV_H
