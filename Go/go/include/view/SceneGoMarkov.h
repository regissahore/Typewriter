#ifndef SCENEGOMARKOV_H
#define SCENEGOMARKOV_H
#include "stable.h"
#include "SceneGo.h"

class GoMarkovGraph;
class ItemGoMarkovOperator;
class ItemGoMarkovEquivalent;

class SceneGoMarkov : public SceneGo
{
    Q_OBJECT
public:
    SceneGoMarkov(QObject *parent = 0);
    QSharedPointer<GoMarkovGraph> generateGoMarkovGraph();
    QSharedPointer<GoMarkovGraph> generateGoMarkovSimpleGraph();
    QSharedPointer<GoMarkovGraph> generateGoMarkovSimpleSubGraph(ItemGoMarkovOperator *last);
    virtual void analysisProbability(const QString filePath) override;
    virtual void analysisCut(const QString filePath) override;
    virtual void analysisPath(const QString filePath) override;
    void save(QDomDocument &document, QDomElement &root) override;
    bool tryOpen(QDomElement &root) override;

protected:
    double _analysisTotalTime;
    double _analysisCount;
    int _analysisCutOrder;
    void initGlobalFeedbackCut(double interval, int count);
    void initGlobalFeedbackPath(double interval, int count);
    QList<ItemGoMarkovEquivalent *> getTopologyOrder(QList<ItemGoMarkovEquivalent *> equivalents);
};

#endif // SCENEGOMARKOV_H
