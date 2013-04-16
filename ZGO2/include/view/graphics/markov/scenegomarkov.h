#ifndef SCENEGOMARKOV_H
#define SCENEGOMARKOV_H
/**
 * The graphics scene for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "scenego.h"

class SceneGOMarkov : public SceneGO
{
    Q_OBJECT
public:
    SceneGOMarkov(QObject *parent = 0);
    bool tryOpen(QDomElement &root);
    GOGraph* generatorGOGraph();
    void analysisProbability(const QString filePath);
};

#endif // SCENEGOMARKOV_H
